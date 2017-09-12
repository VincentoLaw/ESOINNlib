#ifndef SIMPLEAM_H
#define SIMPLEAM_H
#include "ESOINNLibSources/neuron.h"
#include "ESOINNLibSources/esoinn.h"
/*
class AMConnection{
public:
    AMConnection();
    vertex neuron1;
    vertex neuron2;
    double weight;
};

class AMNeuron{
public:
    AMNeuron();
    vertex neuron;
    int timesActive;
    int timesFromActive;
    list<AMConnection> connections;
};

class SimpleAM
{
public:
    SimpleAM(Esoinn * senses, int senses_count);
    ~SimpleAM();
    Esoinn * senses;
    int sensesCount;
    void learn(double ** inputs);
    double ** getAssotiation(double ** inputs);
    list<AMNeuron*> * neurons;
};*/

#endif // SIMPLEAM_H
