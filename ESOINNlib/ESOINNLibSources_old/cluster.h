#pragma once
#include <list>

using namespace std;

class Neuron;

class Cluster{

	private:

		int id;
		double meanDensity;
		Neuron * apex;

	public:
        Cluster(Neuron *delegatorOfCluster, int clusterId);
		~Cluster();
		list<Neuron*> *neuronsList;
		int getId();
		void setId(int data);
		double getDensity();
		Neuron* findApex();
		Neuron *getApex();
        void removeNeuron(Neuron * n);
		double calcMeanDensity();
};

