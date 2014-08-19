#include "neuron.h"
#include "cluster.h"

int Cluster::getId(){
	return this->id;
}

double Cluster::getDensity(){
	return this->meanDensity;
}

Neuron * Cluster::getApex(){
	return this->apex;
}

void Cluster::calcMeanDensity(){
	double res = 0.0;
    for (std::list<Neuron>::iterator it=this->neuronsList->begin(); it != this->neuronsList->end(); ++it){
        res += (*it).getDensity();
    }
	res /= this->neuronsList->size();
	this->meanDensity = res;
}

