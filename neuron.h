#pragma once
#include "connection.h"
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
    	static int acount;
	
	public:
    	
		Neuron(int dimentionSize, double * values);
    	void incSignal(int n = 1);
    	Cluster * getCluster();
    	double getDensity();
    	void setDensity(int data);
};
