#include "neuron.h"
#include "connection.h"
#include "esoinn.h"
#include "cluster.h"

Esoinn::Esoinn(int dimensionSize, double learningRate, int maximalConnectionAge, int lambda, double c1, double c2, double (*distanceFunction)(double *,double *)){//= &commonDistanceFunction
    this->dimensionSize = dimensionSize;
    neuronsList = new std::list<Neuron *>();
}

double Esoinn::calcEuclidNorm(double * vector1, double * vector2, int n){
	double res = 0.0;
	for(int i = 0; i < n; i++){
		res += pow(vector1[i] - vector2[i], 2);
	}
	res = pow(res, 0.5);
}

double Esoinn::calcMeanDistance(Neuron * neuron){
	double res = 0.0;
	Neuron * tmp;
    for (std::list<Connection>::iterator it=neuron->neighboursList->begin(); it != neuron->neighboursList->end(); ++it){
        tmp = (*it).getNeighbourNeuron(neuron);
        res += calcEuclidNorm(neuron->weights, tmp->weights, this->dimensionSize);
    }
	res /= neuron->neighboursList->size();

	return res;
}

double Esoinn::calcPoint(Neuron * neuron){
	return 1 / pow(1 + this->calcMeanDistance(neuron), 2);
}

bool Esoinn::keytoConnect(Neuron * first, Neuron * second){
	double a;
	Cluster * buf;
	if (first->getId() < 0 || second->getId() < 0) return true;
	if (first->getId() == second->getId()) return true;

	Cluster * A = first->getCluster();
	Cluster * B = second->getCluster();

	if(2.0 * A->getDensity() >= A->getApex()->getDensity()){
		a = 0.0;
	}
	else if ((3.0 * A->getDensity() >= A->getApex()->getDensity())
		&&	 (A->getApex()->getDensity() > 2.0 * A->getDensity())){
		a = 0.5;
	}
	else if(A->getApex()->getDensity() > 3.0 * A->getDensity()){
		a = 1.0;
	}

	if(min(first->getDensity(), second->getDensity()) > a * buf->getApex()->getDensity()){
		Cluster::unite(A, B);
		return true;
	}

	return false;
}

bool Esoinn::connectionExist(Neuron * first, Neuron *second){
    for (std::list<Connection>::iterator it=this->connectionsList->begin(); it != this->connectionsList->end(); ++it){
		if(((*it).first == first) && ((*it).second == second)
	    ||(((*it).first == second) && ((*it).second == first))){
	    	return true;
	    }
    }
	return false;
}

bool Esoinn::findFirstWiner(double * inputVector, Neuron * winner, Neuron * secondWinner, int & threshold){
    winner = NULL; secondWinner = NULL;
    double minDist = INFINITY, secondMinDist = INFINITY;//TODO: make values INFINITY
    int neuronsCnt = neuronsList->size();

    if (neuronsCnt < 2)
        return false;

    for (std::list<Neuron *>::iterator it=this->neuronsList->begin(); it != this->neuronsList->end(); ++it){
        minDist = calcDistance((*it)->weights, inputVector);
        if (threshold > minDist)
        {
            secondMinDist = threshold;
            threshold = minDist;
            secondWinner = winner;
            winner = *it;
        }
        else if (secondMinDist > minDist)
        {
            secondMinDist = minDist;
            secondWinner = *it;
        }
    }
    return true;
}

void Esoinn::addNeuron(double * weights){
    neuronsList->push_back(new Neuron(dimensionSize, weights));
}

void Esoinn::addNeuron(double * weights, double threshold){
    Neuron * neuron = new Neuron(dimensionSize, weights);
    neuronsList->push_back(neuron);
    neuron->similarityThreshold = threshold;
}

//TODO: implement this function
void Esoinn::inputSignal(double* inputVector){
/*-----------------1.Initialize-set-of-2-neurons-with-2-first-weights-taken-from-input-------*/
    if (neuronsList->size() < 2){//better count of all input signals
        addNeuron(inputVector);
        return;
    }
/*-----------------1.end-------*/
/*-----------------2.Finding-first-and-second-winner-for-input-signal-------*/
    Neuron *winner, *secondWinner;
    int threshold;
    findFirstWiner(inputVector, winner, secondWinner, threshold);
/*-----------------2.end-------*/
/*-----------------3.add-neuron-if-the-distance-between-inputVector-and-winner-or-secondWinner-is-greater-than-threshold-------*/
    if (winner || secondWinner
        || calcDistance(winner->weights, inputVector) > winner->similarityThreshold
        || calcDistance(secondWinner->weights, inputVector) > secondWinner->similarityThreshold)
    {
        addNeuron(inputVector, threshold);
        winner->similarityThreshold = threshold;
    }
/*-----------------3.end-------*/
    else {
    /*-----------------4.increase-age-of-connection,-which-belongs-to-winner-------*/

        for (std::list<Connection>::iterator it=winner->neighboursList->begin(); it != winner->neighboursList->end(); ++it){
                (*it).incAge();
        }
    /*-----------------4.end.----------------------------------------------------------*/
    /*-----------------5.To-create-connections-between-winner-and-secondWinner-if necessary----------*/
        bool exist = this->connectionExist(winner, secondWinner);
        bool key = this->keytoConnect(winner, secondWinner);
        if(key){
            if(!exist){
                this->addConnection(winner, secondWinner);
                (*(this->connectionsList->end())).setAge(0);
            }
            else{
                this->setConnectionAge(winner, secondWinner);
            }
        }
        else{
            if(exist) this->removeConnection(winner, secondWinner);
        }
    /*-----------------5.end.----------------------------------------------------------*/

    /*-----------------6.Update the density of winner----------------------------------*/
        double point = calcPoint(winner);
        double density = point / winner->getCountSignals();
        winner->setDensity(density);
    /*-----------------6.end.----------------------------------------------------------*/

    /*-----------------7.Increase-signals-of--neuron-winner----------------------------*/
        winner->incSignal();
    /*-----------------7.end.----------------------------------------------------------*/

    /*-----------------8.Adapt weight vectors of winner and it's neighbors-------------*/
        double e1 = 1.0 / winner->getCountSignals();
        double e2 = 1.0 / (100 * winner->getCountSignals());
        for(int i = 0; i < winner->getDim(); i++){
            winner->weights[i] = e1 * (inputVector[i] - winner->weights[i]);
        }
        for(std::list<Connection>::iterator it=winner->neighboursList->begin(); it != winner->neighboursList->end(); ++it){
            for(int i = 0; i < winner->getDim(); i++){
                (*it).getNeighbourNeuron(winner)->weights[i] = e2 * (inputVector[i] - (*it).getNeighbourNeuron(winner)->weights[i]);
            }
        }
    /*-----------------8.end.----------------------------------------------------------------*/

    /*-----------------9.Find-old-edges-and-remove-them--------------------------------*/
        for (std::list<Connection>::iterator it=this->connectionsList->begin(); it != this->connectionsList->end(); ++it){
            if ((*it).getAge() > this->maximalConnectionAge){
                this->removeConnection(*it);
            }
        }
    /*-----------------9.end.----------------------------------------------------------*/

    /*----------------------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------------------*/
    }
}

int main(){
}
