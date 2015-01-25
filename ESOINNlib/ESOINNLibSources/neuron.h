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
        
		Neuron(int dimentionSize, double* weights);
		Neuron(Neuron* v);
		~Neuron();

        double similarityThreshold;
		double * weights;
    	list<Connection*> * neighboursList;
        double point;
    	
		void incSignal();
    	Cluster * getCluster();
    	double getDensity();
		int getDim();
    	int getId();
    	int getCountSignals();
        void setDensity(double data);
    	void setId(int data);
    	Cluster* setArea(Cluster* buf);
};
