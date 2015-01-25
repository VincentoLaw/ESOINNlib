#include "neuron.h"
#include "cluster.h"

Cluster::Cluster(Neuron * delegatorOfCluster, int clusterId)
{
	neuronsList = new list<Neuron*>();
	apex = delegatorOfCluster;
	neuronsList->push_back(apex); 
    id = clusterId;
}

Cluster::~Cluster()
{
	for(list<Neuron *>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it) delete (*it);
	delete neuronsList;
    delete apex;
}

int Cluster::getId()
{
	return id;
}

void Cluster::setId(int data)
{
	id = data;
}

double Cluster::getDensity()
{
	return meanDensity;
}

Neuron * Cluster::getApex()
{
	return apex;
}

double Cluster::calcMeanDensity()
{
	double res = 0.0;
    for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
	{
        res += (*it)->getDensity();
    }
	res /= neuronsList->size();
	meanDensity = res;
	return meanDensity;
}

Neuron* Cluster::findApex()
{
	for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
	{
		if ((*it)->getDensity() > apex->getDensity()) apex = (*it);
		//this->apex = (*it).getDensity() > this->apex->getDensity() ? it : this->apex;
	}
	return apex;
}



