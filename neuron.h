#pragma once
#include "connection.h"
#include "neuron.h"
#include <list>

class Connection;

class Neuron{
private:
    double density;
    double similarityThreshold;
    int dimentionSize;
    int classId;
    double * values;
    std::list<Connection> * neighboursList;
    int winnerTimesCount;
public:
    Neuron(int dimentionSize, double * values);
    void updateDensity();
};
