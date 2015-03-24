#pragma once

#include <list>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <memory>
#include <QDebug>

#define INF 1e15
#define weight unique_ptr<double[]>
#define vertex shared_ptr<Neuron>
#define edge shared_ptr<Connection>
#define cluster shared_ptr<Cluster>

#define neuronIterator list<vertex>::iterator
#define	edgeIterator list<edge>::iterator
#define clusterIterator list<cluster>::iterator



using namespace std;


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

class Esoinn
{

	private:

		//variables
        int dimensionSize;
        int maximalConnectionAge;
        int LT;
        int lambda;
        double c1;
        double c2;
        list<vertex> neuronsList;
        list<edge> connectionsList;
        list<cluster> clustersList;
        int clustersId;

		//methods
        double commonDistanceFunction(double * inputVector, double * checkDistanceVector);

		//TODO another params?
        
        
        vertex addNeuron(double * weights, double threshold);
        /*+*/vertex addNeuron(double *weights);
        vertex addNeuron(vertex neuronToAdd);
        /*+*/edge addConnection(vertex first, vertex second);
        cluster addCluster(vertex delegatorOfCluster);
        /*+*/void removeConnection(edge Edge);
        void removeConnection(edgeIterator &edgeToremove);
        /*+*/void removeConnection(vertex first, vertex second);
        /*+*/void removeNeuron(vertex neuronToRemove);
        /*+*/void removeNeuron(neuronIterator &neuronToRemove);
        /*+*/edge getConnection(vertex first, vertex second);

		//TODO another params?
        double calcDistance(double *weight1, double *weight2);
        double calcMeanDistance(vertex neuron);
        
        /*?*/bool findWiner(double * inputVector, vertex &winner, vertex &secondWinner);
        /*?*/bool needAddConnection(vertex first, vertex second);
        /*?*/bool needUniteClusters(vertex first, vertex second);
        /*?*/void uniteClusters(vertex a, vertex b);
        /*?*/double densityThreshold(double mean, double max);
        /*?*/double similarityThreshold(vertex neuron);
        /*?*/bool isWithinThreshold(vertex firstWinner, vertex secondWinner, double* inputSignal);
        /*?*/void updateDensity(vertex winner);
        /*?*/void adaptWeights(vertex &winner, double* inputVector);
        /*?*/void removeOldConnections();


		
        double calcPoint(vertex neuron);
        double calcEuclidNorm(double * vector1, double * vector2, int n);
        double calcHemmingNorm(double * vector1, double * vector2, int n);
        double externalCalcDistance(double * weight1, double * weight2);
		


		//TODO: params and implementation
		void updateClassLabels();
        void markClasses();
		void separateToSubclasses();
		void removeNoise();

        vertex getNeuron(int neuronIndex);
        edge getConnection(int connectionIndex);

        int getNeuronId(vertex neuron);
        vertex getNeuronById(int id);


    public:

		//Constructor for ESOINN
        //dimensionSize means the size of learning vectors
        //distanceFunction can not be set, it means the function, that calculate distance between vectors

		
		Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2, double (*distanceFunction)(double *,double *));
		/*+*/Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2);
        Esoinn(string fileName);
		~Esoinn();
		//method for input learning vectors as double values
        


        void inputSignal(double *inputVector);
        //void inputSignal(Neuron * inputVector);
		/*+*/void writeStructureToFile(string fileName);
		double ** getStructure();
		//returns main neuron that represent this input vector
        void clearWinners();
		//int neuronClassId(double * inputVector);

        void saveStateToFile(string fileName);
        void loadStateFromFile(string fileName);

		//bool saveNetworkData(string fileName);
        //bool loadNetworkData(string fileName);

};


