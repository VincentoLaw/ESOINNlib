#pragma once
#include <list>
#include <memory>
#include <string>
#include <time.h>
#define vertex shared_ptr<Neuron>
#define edge shared_ptr<Connection>
#define cluster shared_ptr<Cluster>

#define neuronIterator list<vertex>::iterator
#define edgeIterator list<edge>::iterator

class Cluster;
class Connection;


using namespace std;



class Neuron{

	private:

		double density;
    	int dimentionSize;

    	int classId;

    	int winerTimesCount;

	public:
        
		Neuron(int dimentionSize, double* weights);
        Neuron(vertex v);
		~Neuron();

        double similarityThreshold;
        double *weights;
        list<edge> neighboursList;
        double point;
        cluster area;

        bool winInThisIter;
        int allTimeWin;
    	
		void incSignal();
        cluster getCluster();
    	double getDensity();
		int getDim();
    	int getId();
    	int getCountSignals();
        void setDensity(double data);
    	void setId(int data);
        cluster setArea(cluster buf);
        string getNeuronData();
};
