#pragma once
#include "connection.h"
#include "cluster.h"
#include <list>

using namespace std;

class Cluster;
class Connection;

class Neuron{

	private:

		double density;

    	int dimentionSize;
    	int classId;
    	int winerTimesCount;
    	static int acount;

	public:
        double similarityThreshold;
		double * weights;
    	list<Connection*> * neighboursList;
		Neuron(int dimentionSize, double * values);
    	void incSignal();
    	Cluster * getCluster();
    	double getDensity();
		int getDim();
    	int getId();
    	int getCountSignals();
    	void setDensity(int data);
    	void setId(int data);
    	void remove();
};
