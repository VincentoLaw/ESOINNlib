#pragma once
#include <list>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

#define INF 1e15
//TODO change name or put in class constants

/*
Neuron can be changed to Node
Connection can be changed to Edge
all names can be changed to their analogy names in "how_to_use_soinn.pdf" and esoinn c# project

The rules of naming:
class, structures names  starting with big letter
variables names starting with small letter
*/
class Cluster;
class Neuron;
class Connection;

class Esoinn{

	private:

		//variables
        int dimensionSize;
        int maximalConnectionAge;
        int LT;
        int lambda;
        double c1;
        double c2;
        list<Neuron *> * neuronsList;
        list<Connection *> * connectionsList;
        list<Cluster *> * clustersList;

		//methods
        double commonDistanceFunction(double * inputVector, double * checkDistanceVector);

		//TODO another params?
        void addNeuron(Neuron * neuronToAdd);
        Neuron * addNeuron(double * weights);
        Neuron * addNeuron(double * weights, double threshold);

        Cluster* addCluster(Neuron * delegatorOfCluster);

		//TODO another params?
        void removeNeuron(Neuron * neuronToRemove);
        void removeNeuron(list<Neuron*>::iterator neuronToRemove);
        Connection * addConnection(Neuron * first, Neuron * second);
        void removeConnection(Neuron * first, Neuron * second);
        void removeConnection(Connection * edge);
        Connection * connectionExist(Neuron * first, Neuron * second);
        bool keytoConnect(Neuron * first, Neuron * second);
        bool findWiner(double * inputVector, Neuron * &winner, Neuron * &secondWinner, int & threshold);

        double calcDistance(double * weight1, double * weight2);
		double calcMeanDistance(Neuron * neuron);
        double calcPoint(Neuron * neuron);
       	double calcEuclidNorm(double * vector1, double * vector2, int n);
       	double externalCalcDistance(double * weight1, double * weight2);
		int calcHemmingNorm(double * vector1, double * vector2, int n);


		//TODO: params and implementation
        void markClasses();
		void separateToSubclasses();

		double distance(Neuron * first, Neuron * second);

        Neuron * getNeuron(int neuronIndex);

		Connection * getConnection(Neuron * first, Neuron * second);
        Connection * getConnection(int connectionIndex);


    public:

		//Constructor for ESOINN
        //dimensionSize means the size of learning vectors
        //distanceFunction can not be set, it means the function, that calculate distance between vectors

        //Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2, double (*distanceFunction)(double *,double *));
		Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2);
		~Esoinn();
		//method for input learning vectors as double values
        void inputSignal(double * inputVector);
        void inputSignal(Neuron * inputVector);
        void writeStructureToFile(string fileName);
        double ** getStructure();

		//returns main neuron that represent this input vector
        void classify();

		int neuronClassId(double * inputVector);

		bool saveNetworkData(string fileName);
        bool loadNetworkData(string fileName);

};


