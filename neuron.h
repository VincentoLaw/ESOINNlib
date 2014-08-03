#pragma once
#include "connection.h"
#include "neuron.h"
#include <list>

class Connection;

class Neuron{
	
	private:
    	
		double density;
    	double similarityThreshold;
    	int dimentionSize;
    	int classId;
    	double * weights;
    	std::list<Connection> * neighboursList;
    	int winnerTimesCount = 0;
	
	public:
    	
		Neuron(int dimentionSize, double * values);
    	void updateDensity();
    	void incSignal(int n = 1);
};
