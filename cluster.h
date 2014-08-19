#pragma once
#include "neuron.h"
#include <list>
using namespace std;

class Neuron;

class Cluster{

	private:

		int id;
		double meanDensity;
		Neuron * apex;

	public:
		list<Neuron> * neuronsList;
		int getId();
		double getDensity();
		Neuron * getApex();
		static void unite(Cluster *a, Cluster * b );
		void separate();
		void calcMeanDensity();
};
