#include "neuron.h"
#include "connection.h"
#include "esoinn.h"
#include "cluster.h"

#define NeuronIterator list<Neuron*>::iterator
Esoinn::Esoinn(int dimensionSize, double learningRate, int maximalConnectionAge, int lambda, double c1, double c2, double (*distanceFunction)(double *,double *)){//= &commonDistanceFunction
    this->dimensionSize = dimensionSize;
    clustersCnt = 0;
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
    for (list<Connection*>::iterator it = neuron->neighboursList->begin(); it != neuron->neighboursList->end(); ++it){
        tmp = (*it)->getNeighbourNeuron(neuron);
        res += calcEuclidNorm(neuron->weights, tmp->weights, dimensionSize);
    }
	res /= neuron->neighboursList->size();

	return res;
}

double Esoinn::calcPoint(Neuron * neuron){
	return 1 / pow(1 + calcMeanDistance(neuron), 2);
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
		for(list<Cluster*>::iterator it = clustersList->begin(); it != clustersList->end(); ++it){
			if((*it) == B) clustersList->erase(it);
			break;
		}
		Cluster::unite(A, B);

		return true;
	}

	return false;
}



Connection * Esoinn::getConnection(Neuron * first, Neuron * second){
	for (list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it){
		if(((*it)->first == first) && ((*it)->second == second)
	    ||(((*it)->first == second) && ((*it)->second == first))){
	    	return (*it);
	    }
	}
	return NULL;
}

bool Esoinn::findWiner(double * inputVector, Neuron * winner, Neuron * secondWinner, int & threshold){
    winner = NULL; secondWinner = NULL;
    double minDist = INF, secondMinDist = INF;//TODO: make values INF
    int neuronsCnt = neuronsList->size();

    if (neuronsCnt < 2)
        return false;

    for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
        minDist = calcDistance((*it)->weights, inputVector);
        if (threshold > minDist){
            secondMinDist = threshold;
            threshold = minDist;
            secondWinner = winner;
            winner = *it;
        }
        else if (secondMinDist > minDist){
            secondMinDist = minDist;
            secondWinner = *it;
        }
    }
    return true;
}

Neuron * Esoinn::addNeuron(double * weights){
    Neuron * neuron = new Neuron(dimensionSize, weights);
    neuronsList->push_back(neuron);
    return neuron;
}

Neuron * Esoinn::addNeuron(double * weights, double threshold){
    Neuron * neuron = new Neuron(dimensionSize, weights);
    neuronsList->push_back(neuron);
    neuron->similarityThreshold = threshold;
    return neuron;
}

void Esoinn::removeNeuron(Neuron * neuronToRemove){

	for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
		if((*it) == neuronToRemove){
			neuronsList->erase(it);
		}
	}
	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it){
		if(((*it)->first == neuronToRemove) || ((*it)->second == neuronToRemove)){
			connectionsList->erase(it);
		}
	}
	for(list<Cluster*>::iterator it = clustersList->begin(); it != clustersList->end(); ++it){
		for(list<Neuron*>::iterator j = (*it)->neuronsList->begin(); j != (*it)->neuronsList->end(); ++j){
			if((*j) == neuronToRemove){
				(*it)->neuronsList->erase(j);
			}
		}
	}
	for(list<Connection*>::iterator it = neuronToRemove->neighboursList->begin(); it != neuronToRemove->neighboursList->end(); ++it){
		for(list<Connection*>::iterator j = (*it)->getNeighbourNeuron(neuronToRemove)->neighboursList->begin(); j != (*it)->getNeighbourNeuron(neuronToRemove)->neighboursList->end(); ++j){
			if((*j) == (*it)){
				(*it)->getNeighbourNeuron(neuronToRemove)->neighboursList->erase(j);
			}
		}
	}
	neuronToRemove->remove();
}

void Esoinn::removeNeuron(list<Neuron*>::iterator neuronToRemove){
	neuronsList->erase(neuronToRemove);

	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it){
		if(((*it)->first == *neuronToRemove) || ((*it)->second == *neuronToRemove)){
			connectionsList->erase(it);
		}
	}
	for(list<Cluster*>::iterator it = clustersList->begin(); it != clustersList->end(); ++it){
		for(list<Neuron*>::iterator j = (*it)->neuronsList->begin(); j != (*it)->neuronsList->end(); ++j){
			if((*j) == *neuronToRemove){
				(*it)->neuronsList->erase(j);
			}
		}
	}
	for(list<Connection*>::iterator it = (*neuronToRemove)->neighboursList->begin(); it != (*neuronToRemove)->neighboursList->end(); ++it){
		for(list<Connection*>::iterator j = (*it)->getNeighbourNeuron(*neuronToRemove)->neighboursList->begin(); j != (*it)->getNeighbourNeuron(*neuronToRemove)->neighboursList->end(); ++j){
			if((*j) == (*it)){
				(*it)->getNeighbourNeuron(*neuronToRemove)->neighboursList->erase(j);
			}
		}
	}
	(*neuronToRemove)->remove();
}

void Esoinn::addCluster(Neuron * delegatorOfCluster){
    clustersList->push_back(new Cluster(delegatorOfCluster, clustersCnt));
    clustersCnt++;
}

Connection * Esoinn::addConnection(Neuron * first, Neuron * second){
	Connection * connection = new Connection(first, second);
	this->connectionsList->push_back(connection);
	first->neighboursList->push_back(connection);
	second->neighboursList->push_back(connection);
	return connection;
}

void Esoinn::removeConnection(Neuron * first, Neuron * second){
	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it){
		if(((*it)->first == first) && ((*it)->second == second) ||
		  ((*it)->first == second) && ((*it)->second == first)){
			(*it)->remove();
			for(list<Connection*>::iterator j = first->neighboursList->begin(); j != first->neighboursList->end(); ++j){
				if (j == it){
					first->neighboursList->erase(j);
					break;
				}
			}
			for(list<Connection*>::iterator j = second->neighboursList->begin(); j != second->neighboursList->end(); ++j){
				if(j == it){
					second->neighboursList->erase(j);
					break;
				}
			}
			connectionsList->erase(it);

		}
	}
}

void Esoinn::removeConnection(Connection * edge){
	edge->remove();
	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it){
		if(edge == (*it)){
			connectionsList->erase(it);
			for(list<Connection*>::iterator j = edge->first->neighboursList->begin(); j != edge->first->neighboursList->end(); ++j){
				if((*j) == edge){
					edge->first->neighboursList->erase(j);
					break;
				}
			}
			for(list<Connection*>::iterator j = edge->second->neighboursList->begin(); j != edge->second->neighboursList->end(); ++j){
				if((*j) == edge){
					edge->second->neighboursList->erase(j);
					break;
				}
			}
			break;
		}
	}
}

void path(Neuron * top, Cluster * bag){
	top->setId(bag->getId());
	bag->neuronsList->push_back(top);
	for(list<Connection*>::iterator it = top->neighboursList->begin(); it != top->neighboursList->end(); ++it){
		if((*it)->getNeighbourNeuron(top)->getId() == -1 && (*it)->getNeighbourNeuron(top)->getDensity() < top->getDensity() ){
			path((*it)->getNeighbourNeuron(top), bag);
		}
	}
}

bool cmp_density(Neuron *a, Neuron *b){
	return a->getDensity() > b->getDensity();
}
void Esoinn::markClasses(){
	list<Neuron*> vertexQueue;
	for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
		(*it)->setId(-1);
		vertexQueue.push_back(*it);
	}
	vertexQueue.sort(cmp_density);

	int classCount = 0;
	for(list<Neuron*>::iterator it = vertexQueue.begin(); it != vertexQueue.end(); ++it){
		if((*it)->getId() == -1){
			(*it)->setId(classCount);
			//path(*it, classCount++);
			path(*it, (*it)->getCluster());
		}
	}
}
void Esoinn::separateToSubclasses(){
	Neuron* a;
	Neuron* b;
	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it){
		a = (*it)->first, b = (*it)->second;
		if(keytoConnect(a, b)){
			Cluster::unite(a->getCluster(), b->getCluster());
		}
		else{
			removeConnection(*it);
		}
	}
}


void Esoinn::classify(){

}
//TODO: implement this function
void Esoinn::inputSignal(double* inputVector){

/*-----------------1.Initialize-set-of-2-neurons-with-2-first-weights-taken-from-input*/
    if (neuronsList->size() < 2){//better count of all input signals
        Neuron * neuron = addNeuron(inputVector);
        addCluster(neuron);
        return;
    }
/*-----------------1.end--------------------------------------------------------------*/

/*-----------------2.Finding-first-and-second-winner-for-input-signal-----------------*/
    Neuron *winner, *secondWinner;
    int threshold;
    findWiner(inputVector, winner, secondWinner, threshold);
/*-----------------2.end-------------------------------------------------------------*/

/*-----------------3.add-neuron-if-the-distance-between-inputVector-and-winner-or-secondWinner-is-greater-than-threshold-------*/
    if (winner || secondWinner
        || calcDistance(winner->weights, inputVector) > winner->similarityThreshold
        || calcDistance(secondWinner->weights, inputVector) > secondWinner->similarityThreshold)
    {
        addNeuron(inputVector, threshold);
        winner->similarityThreshold = threshold;
    }
/*-----------------3.end--------------------------------------------------------------*/
    else {
/*-----------------4.increase-age-of-connection,-which-belongs-to-winner--------------*/

        for (list<Connection*>::iterator it = winner->neighboursList->begin(); it != winner->neighboursList->end(); ++it){
                (*it)->incAge();
        }
/*----------------4.end.--------------------------------------------------------------*/

/*----------------5.To-create-connections-between-winner-and-secondWinner-if necessary*/
    	Connection* edge = getConnection(winner, secondWinner);
        bool key = keytoConnect(winner, secondWinner);
        if(key){
            if(!edge){
                addConnection(winner, secondWinner);
            }
            else{
                edge->setAge(0);
            }
        }
        else{
             removeConnection(edge);
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

    /*-----------------8.Adapt weight vectors of winner and it's neighbours------------*/
        double e1 = 1.0 / winner->getCountSignals();
        double e2 = 1.0 / (100 * winner->getCountSignals());
        for(int i = 0; i < winner->getDim(); i++){
            winner->weights[i] = e1 * (inputVector[i] - winner->weights[i]);
        }
        for(list<Connection*>::iterator it = winner->neighboursList->begin(); it != winner->neighboursList->end(); ++it){
            for(int i = 0; i < winner->getDim(); i++){
                (*it)->getNeighbourNeuron(winner)->weights[i] = e2 * (inputVector[i] - (*it)->getNeighbourNeuron(winner)->weights[i]);
            }
        }
    /*-----------------8.end.-----------------------------------------------------------*/

    /*-----------------9.Find-old-edges-and-remove-them---------------------------------*/
        for (list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it){
            if ((*it)->getAge() > maximalConnectionAge){
                removeConnection(*it);
            }
        }
    /*-----------------9.end.-----------------------------------------------------------*/

    /*---------------- 10.Separate-all-classes-on--subclasses---------------------------*/
		markClasses();
		separateToSubclasses();
	/*---------------- 10.end.----------------------------------------------------------*/

	/*-----------------11.-Delete-nodes-polluted-by-noise-------  ----------------------*/
		double meanDensityA = 0.0;
    	for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
        	meanDensityA += (*it)->getDensity();
    	}
		meanDensityA /= neuronsList->size();

		for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
			if(((*it)->neighboursList->size() == 2) && ((*it)->getDensity() < c1 * meanDensityA)) removeNeuron(it);
			if(((*it)->neighboursList->size() == 1) && ((*it)->getDensity() < c2 * meanDensityA)) removeNeuron(it);
			if(!(*it)->neighboursList->size()) removeNeuron(it);
		}
    /*-----------------11.end.----------------------------------------------------------*/

    /*-----------------12.Classify-all-nodes-by-the-labels(not-for-life-long-learning)--*/
    	int count = 0;
		for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
			(*it)->setId(-1);
		}
		list<Cluster*>::iterator j = clustersList->begin();
		(*j)->neuronsList->clear();
		for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
			if((*it)->getId() == -1){
				count++;
				if(j == clustersList->end()){
					clustersList->push_back(new Cluster(*it, count));
					j++;
					path((*it), (*j));
				}
				else {
					j++;
					path((*it), (*j));
				}
			}
		}
	//Maybe a little count of clusters left unchanged? But it cant be happend in theory
    /*-----------------12.end.----------------------------------------------------------*/
    }
}

double Esoinn::calcDistance(double * a, double * b){

}

int main(){
}
