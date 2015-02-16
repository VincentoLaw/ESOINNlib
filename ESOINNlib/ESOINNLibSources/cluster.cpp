#include "neuron.h"
#include "cluster.h"
#include <QDebug>

Cluster::Cluster(Neuron * delegatorOfCluster, int clusterId)
{
	neuronsList = new list<Neuron*>();
	apex = delegatorOfCluster;
	neuronsList->push_back(apex); 
    id = clusterId;
}

Cluster::~Cluster()
{
    qDebug() << "C" << neuronsList;
    if (neuronsList){
        for(list<Neuron *>::iterator it = neuronsList->begin(); it != neuronsList->end();) {
            qDebug() <<*it;
            Neuron * n = *it;
            qDebug() <<"C1";
            it = neuronsList->erase(it);
            qDebug() <<"C2";
            //if (n)
            //    delete n;
            qDebug() <<"C3";

        }
        //delete neuronsList;
        //delete apex;
    }
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

void Cluster::removeNeuron(Neuron * n){
    if (n == apex)//TODO сравнение указателей?
        findApex();
    neuronsList->remove(n);
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



