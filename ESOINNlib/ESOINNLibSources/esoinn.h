#pragma once
#include <list>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <QDebug>

using namespace std;

#define INF 1e15
#define NeuronIterator list<Neuron*>::iterator
#define	EdgeIterator list<Connection*>::iterator
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
        

		//methods
        double commonDistanceFunction(double * inputVector, double * checkDistanceVector);

		//TODO another params?
        
        
        Neuron * addNeuron(double * weights, double threshold);

        

		//TODO another params?
        
        
        /*?*/bool findWiner(double * inputVector, Neuron * &winner, Neuron * &secondWinner);
        /*?*/bool needAddConnection(Neuron *first, Neuron *second);
        /*?*/bool needUniteClusters(Neuron *first, Neuron *second);
        /*?*/void uniteClusters(Neuron* a, Neuron* b);
        /*?*/double densityThreshold(double mean, double max);
        /*?*/double similarityThreshold(Neuron* neuron);
        /*?*/bool isWithinThreshold(Neuron* firstWinner, Neuron* secondWinner, double* inputSignal);
        /*?*/void updateDensity(Neuron* winner);
		/*?*/void adaptWeights(Neuron *&winner, double* inputVector);
        /*?*/void removeOldConnections();

        
		
        double calcPoint(Neuron * neuron);
       	double calcEuclidNorm(double * vector1, double * vector2, int n);
       	double calcHemmingNorm(double * vector1, double * vector2, int n);
		double externalCalcDistance(double * weight1, double * weight2);
		


		//TODO: params and implementation
		void updateClassLabels();
        void markClasses();
		void separateToSubclasses();
		void removeNoise();

        Neuron * getNeuron(int neuronIndex);
        Connection * getConnection(int connectionIndex);


    public:

		//Constructor for ESOINN
        //dimensionSize means the size of learning vectors
        //distanceFunction can not be set, it means the function, that calculate distance between vectors
		list<Neuron *> * neuronsList;
        list<Connection *> * connectionsList;
        list<Cluster *> * clustersList;
		
		Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2, double (*distanceFunction)(double *,double *));
		/*+*/Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2);
		~Esoinn();
		//method for input learning vectors as double values
        
		/*+*/Neuron * addNeuron(double * weights);
		Neuron* addNeuron(Neuron * neuronToAdd);
        /*+*/Connection * addConnection(Neuron * first, Neuron * second);
		Cluster* addCluster(Neuron * delegatorOfCluster);
		/*+*/void removeConnection(Connection * edge);
		void removeConnection(list<Connection*>::iterator &edgeToremove);
		/*+*/void removeConnection(Neuron * first, Neuron * second);
		/*+*/void removeNeuron(Neuron * neuronToRemove);
		/*+*/void removeNeuron(list<Neuron*>::iterator &neuronToRemove);
		/*+*/Connection *getConnection(Neuron * first, Neuron * second);
		
		void inputSignal(double * inputVector);
        //void inputSignal(Neuron * inputVector);
        double calcDistance(double * weight1, double * weight2);
        double calcMeanDistance(Neuron * neuron);
		/*+*/void writeStructureToFile(string fileName);
		double ** getStructure();
		//returns main neuron that represent this input vector
        void Esoinn::clearWinners();
		//int neuronClassId(double * inputVector);

		//bool saveNetworkData(string fileName);
        //bool loadNetworkData(string fileName);

};


