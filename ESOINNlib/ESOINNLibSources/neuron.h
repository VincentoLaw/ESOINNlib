#pragma once
#include <list>

using namespace std;

class Cluster;
class Connection;

class Neuron{

	private:

		double density;
    	int dimentionSize;
    	int classId;
    	Cluster* area;
    	int winerTimesCount;

	public:
        double similarityThreshold;
		double * weights;
    	list<Connection*> * neighboursList;
		Neuron(int dimentionSize, double * values);
		~Neuron();
    	void incSignal();
    	Cluster * getCluster();
    	double getDensity();
		int getDim();
    	int getId();
    	int getCountSignals();
    	void setDensity(int data);
    	void setId(int data);
    	void setArea(Cluster* buf);
    	void remove();
};
