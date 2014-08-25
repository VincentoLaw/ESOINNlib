#pragma once
#include "neuron.h"
#include "connection.h"
#include <list>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

#define INFINITY 1e15
//TODO change name or put in class constants

/*
Neuron can be changed to Node
Connection can be changed to Edge
all names can be changed to their analogy names in "how_to_use_soinn.pdf" and esoinn c# project

The rules of naming:
class, structures names  starting with big letter
variables names starting with small letter
*/

class Esoinn{

	private:

		//variables
        int dimensionSize;
        int maximalConnectionAge;
        double lambda;
        double c1;
        double c2;
        list<Neuron *> * neuronsList;
        list<Connection> * connectionsList;
        list<Cluster> classesList;

		//methods
        double commonDistanceFunction(double * inputVector, double * checkDistanceVector);

		//TODO another params?
        void addNeuron(Neuron * neuronToAdd);
        void addNeuron(double * weights);
        void addNeuron(double * weights, double threshold);

		//TODO another params?
        void removeNeuron(Neuron * neuronToRemove);
        void addConnection(Neuron * first, Neuron * second);
        void removeConnection(Neuron * first, Neuron * second);
        void removeConnection(Connection edge);
        bool connectionExist(Neuron * first, Neuron * second);
        bool keytoConnect(Neuron * first, Neuron * second);

        bool findFirstWiner(double * inputVector, Neuron * winner, Neuron * secondWinner, int & threshold);

		list<Neuron> getNeighbors(Neuron * neuron);

        double calcDistance(double * weight1, double * weight2);
		double calcMeanDistance(Neuron * neuron);
        double calcPoint(Neuron * neuron);
       	double calcEuclidNorm(double * vector1, double * vector2, int n);
		//TODO: params and implementation
        void separateToSubclasses();
        Neuron* findWiner(double inputVector);
        Neuron* findSecondWiner(double inputVector, Neuron * firstWiner);

		double distance(Neuron * first, Neuron * second);

        Neuron * getNeuron(int neuronIndex);

		int getNeuronIndex(Neuron * neuron);

		int getConnectionIndex(Connection * connection);
        int getConnectionIndex(Neuron * first, Neuron * second);

		Connection * getConnection(Neuron * first, Neuron * second);
        Connection * getConnection(int connectionIndex);

		int getConnectionAge(int connectionIndex);
        int getConnectionAge(Connection * connection);
        int getConnectionAge(Neuron * first, Neuron * second);

        int setConnectionAge(int connectionIndex, int age = 0);
        int setConnectionAge(Connection * connection, int age = 0);
        int setConnectionAge(Neuron * first, Neuron * second, int age = 0);



    public:

		//Constructor for ESOINN
        //dimensionSize means the size of learning vectors
        //distanceFunction can not be set, it means the function, that calculate distance between vectors

		Esoinn(int dimensionSize, double learningRate, int maximalConnectionAge, int lambda, double c1, double c2, double (*distanceFunction)(double *,double *));

		//method for input learning vectors as double values
        void inputSignal(double * inputVector);
        void inputSignal(Neuron * inputVector);

		//returns main neuron that represent this input vector
        Neuron * classify(double * inputVector);

		int neuronClassId(double * inputVector);

		bool saveNetworkData(string fileName);
        bool loadNetworkData(string fileName);

};


