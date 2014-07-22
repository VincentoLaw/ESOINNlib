#pragma once
#include "neuron.h"
#include "connection.h"
#include <list>
#include <string>

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
        std::list<Neuron> * neuronsList;
        std::list<Connection> * connectionsList;
        //store Neurons, that represent classes
        std::list<Neuron> classesList;
        //methods
        double commonDistanceFunction(double * inputVector, double * checkDistanceVector);
        //TODO another params?
        void addNeuron(Neuron * neuronToAdd);
        //TODO another params?
        void removeNeuron(Neuron * neuronToRemove);
        void addConnection(Neuron* first, Neuron * second);
        void removeConnection(Neuron * first, Neuron * second);
        bool connectionExist(Neuron * first, Neuron * second);
        std::list<Neuron> getNeighbors(Neuron * neuron);
        double calcMeanDistance(Neuron * neuron);
        double calcPoint(Neuron * neuron);
        //TODO: params and implementation
        void separateToSubclasses();
        void findWiner(double inputVector);
        double distance(Neuron * first, Neuron * second);
    public:
        //Constructor for ESOINN
        //dimensionSize means the size of learning vectors
        //distanceFunction can not be set, it means the function, that calculate distance between vectors
        Esoinn(int dimensionSize, double learningRate, int maximalConnectionAge, int lambda, double (*distanceFunction)(double *,double *));
        //method for input learning vectors as double values
        void inputSignal(double * inputVector);
        void inputSignal(Neuron * inputVector);
        //returns main neuron that represent this input vector
        Neuron * classify(double * inputVector);
        int neuronClassId(double * inputVector);
        int getNodesCount();
        int getConnectionsCount();

        //I thought it should be private functions
        //?
        Neuron * getNeuron(int neuronIndex);
        int getNeuronIndex(Neuron * neuron);
        int getConnectionIndex(Connection * connection);
        Connection * getConnection(int connectionIndex);
        int getConnectionAge(int connectionIndex);
        int getConnectionAge(Connection * connection);

        bool saveNetworkData(std::string fileName);
        bool loadNetworkData(std::string fileName);

};


