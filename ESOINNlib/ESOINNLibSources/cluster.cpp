#include "neuron.h"
#include "cluster.h"

Cluster::Cluster(vertex delegatorOfCluster, int clusterId)
{
    apex = delegatorOfCluster;
    neuronsList.push_back(apex);
    id = clusterId;
}

Cluster::~Cluster()
{
    //for(auto it = neuronsList->begin(); it != neuronsList->end(); ++it) delete (*it);
    //delete neuronsList;
    //delete apex;
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

vertex Cluster::getApex()
{
	return apex;
}

vertex Cluster::setApex(vertex data)
{
    apex = data;
    return apex;
}

double Cluster::calcMeanDensity()
{
    auto res = 0.0;
    for(auto &it : neuronsList)
	{
        res += it->getDensity();
    }
    res /= neuronsList.size();
	meanDensity = res;
	return meanDensity;
}

void Cluster::setDensity(double dens)
{
    meanDensity = dens;
}

vertex Cluster::findApex()
{
    if (neuronsList.size())
    {
        if (!apex) apex = *(neuronsList.begin());
        for (auto &it : neuronsList)
        {
            if (it->getDensity() > apex->getDensity()) apex = it;
        }
    }
	return apex;
}



