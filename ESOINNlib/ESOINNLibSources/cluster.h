#pragma once
#include <list>
#include <memory>

#define vertex shared_ptr<Neuron>
#define neuronIterator list<vertex>::iterator


using namespace std;

class Neuron;

class Cluster
{

	private:

		int id;
		double meanDensity;

	public:
        Cluster(vertex delegatorOfCluster, int clusterId);
		~Cluster();
        list<vertex> neuronsList;
		int getId();
		void setId(int data);
		double getDensity();
        vertex findApex();
        vertex getApex();
        vertex setApex(vertex data);
		double calcMeanDensity();

        void setDensity(double density);
        vertex apex;
};

