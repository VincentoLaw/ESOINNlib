#include "neuron.h"
#include "cluster.h"

Cluster::Cluster(Neuron * delegatorOfCluster, int clusterId){
    apex = delegatorOfCluster;
    id = clusterId;
}

int Cluster::getId(){
	return id;
}

double Cluster::getDensity(){
	return meanDensity;
}

Neuron * Cluster::getApex(){
	return apex;
}

void Cluster::calcMeanDensity(){
	double res = 0.0;
    for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
        res += (*it)->getDensity();
    }
	res /= neuronsList->size();
	meanDensity = res;
}
void Cluster::findApex(){
	for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
		if ((*it)->getDensity() > apex->getDensity()) apex = (*it);
		//this->apex = (*it).getDensity() > this->apex->getDensity() ? it : this->apex;
	}
}

void Cluster::remove(){
	delete this;
}

void Cluster::unite(Cluster* A, Cluster* B){
	list<Neuron*>::iterator it = A->neuronsList->end();
	A->neuronsList->splice(it, (*B->neuronsList));
	A->calcMeanDensity();
	A->findApex();
	B->remove();
}

