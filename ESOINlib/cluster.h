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
        Cluster(Neuron * delegatorOfCluster, int clusterId);
		~Cluster();
		list<Neuron*> * neuronsList;
		int getId();
		double getDensity();
		void findApex();
		Neuron * getApex();
		static void unite(Cluster *a, Cluster * b );
		void separate();
		void remove();
		void calcMeanDensity();
};
