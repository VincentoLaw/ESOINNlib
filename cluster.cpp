#include "cluster.h"


int Cluster::getId(){
	return this->id;
}

double Cluster::getDensity(){
	return this->density;
}

Neuron * Cluster::getApex(){
	return this->apex;
}

void Cluster::calcMeanDensity(){
	double res = 0.0;
	for(int i = 0; i < this->neuronsList.size(); i++){
		res += this->neuronsList[i]->getDensity();
	}
	res /= this->neuronsList.size();
	return res;
}
