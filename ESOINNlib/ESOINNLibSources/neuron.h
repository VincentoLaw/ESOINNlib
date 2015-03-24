#pragma once
#include <list>
#include <memory>
#include <time.h>
#define weight unique_ptr<double[]>
#define vertex shared_ptr<Neuron>
#define edge shared_ptr<Connection>
#define cluster shared_ptr<Cluster>

#define neuronIterator list<vertex>::iterator
#define edgeIterator list<edge>::iterator

class Cluster;
class Connection;


using namespace std;



class Neuron
{

	private:

		double density;
    	int dimentionSize;
    	int classId;
        bool classified;
    	int winerTimesCount;
        cluster area;

    public:
        
        Neuron(int dimentionSize, double* weights);
        Neuron(vertex v);
		~Neuron();

        double similarityThreshold;
        double *weights;
        list<edge> neighboursList;
        double point;

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
        void setStatus(bool flag);
        bool isClassified();

        string getNeuronData();
        void setNeuronData(double simTh, double Point, bool winned, int allwins, double dens, int classid, int winCnt);
        cluster setArea(cluster buf);

        cluster setCluster(cluster buf);
};
