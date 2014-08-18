#pragma once
#include "neuron.h"
using namespace std;

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
