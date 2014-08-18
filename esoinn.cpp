#include "neuron.h"
#include "esoinn.h"
#include "cluster.h"

Esoinn::Esoinn(int dimensionSize, double learningRate, int maximalConnectionAge, int lambda, double (*distanceFunction)(double *,double *)){//= &commonDistanceFunction
    this->dimensionSize = dimensionSize;
    neuronsList = new std::list<Neuron>();
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
	for(int i = 0; i < neuron->neighboursList->size(); i++){
		tmp = neuron->neighboursList[i]->getNeighbourNeuron(neuron);
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
	for(int i = 0; i < this->connectionsList->size(); i++){
		if((connectionsList[i]->first == first) && (connectionsList[i]->second == second)
	    ||((connectionsList[i]->first == second) && (connectionsList[i]->second == first))){
	    	return true;
	    }
	}
	return false;
}
//TODO: implement this function
void Esoinn::inputSignal(double * inputVector){

/*-----------------5.increase-age-of-connection,-which-belongs-to-a1-winner-------*/
	Neuron *a1, *a2;
	
	a1 = findFirstWiner(inputVector);
	a2 = findSecondWiner(inputVector, a1);
	
	for(int i = 0; i < a1->neighboursList->size(); i++){
			a1->neighboursList[i]->incAge();
	}
/*-----------------5-end.----------------------------------------------------------*/

/*-----------------6.To-create-connections-between-a1-and-a2-if necessary----------*/
	bool exist = this->connectionExist(a1, a2);
	bool key = this->keytoConnect(a1, a2);
	if(key){
		if(!exist){
			this->addConnection(a1, a2);
			int n = this->connectionsList->size();
			this->connectionsList[n - 1]->setAge(0);
		}
		else{
			this->setConnectionAge(a1, a2);
		}
	}
	else{
		if(exist) this->removeConnection(a1, a2);
	}
/*-----------------6.end.----------------------------------------------------------*/

/*-----------------7.Increase-signals-of--neuron-winner----------------------------*/
	a1->incSignal();
/*-----------------7-end.----------------------------------------------------------*/

/*-----------------8.Update the density of winner----------------------------------*/
	double point = calcPoint(a1);
	double density = point / a1->getCountSignals();
	a1->setDensity(density);
/*-----------------8-end.----------------------------------------------------------*/

/*-----------------9.Find-old-edges-and-remove-them--------------------------------*/
	for(int i = 0; i < connectionsList->size(); i++){
		if (connectionsList[i]->getAge() > this->maximalConnectionAge){
			this->removeConnection(this->connectionsList[i]);
		}
	}
/*-----------------9-end.----------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
}
