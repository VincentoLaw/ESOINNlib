#include "neuron.h"
#include "cluster.h"
#include "connection.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>

Neuron::Neuron(int dimentionSize, double * weights = NULL){
        srand(time(NULL));
        this->neighboursList = new list<Connection *>();
        this->dimentionSize = dimentionSize;
        this->weights = new double[dimentionSize];
        for (int i = 0; i < dimentionSize; i++){
            //TODO: in what borders random values?
            if (weights == NULL)
                this->weights[i] = rand() % 1000;
            else this->weights[i] = weights[i];
        }
        this->area = NULL;
        this->classId = -1;
        this->density = 0;
        this->winerTimesCount = 0;
}

Neuron::~Neuron(){
	for(list<Connection *>::iterator it = neighboursList->begin(); it != neighboursList->end(); ++it) delete (*it);
	delete neighboursList;
	delete area;
}

void Neuron::incSignal(){
	winerTimesCount++;
}

void Neuron::setId(int data){
	classId = data;
}

void Neuron::setDensity(int data){
	density = data;
}

void Neuron::setArea(Cluster* buf){
	this->area = buf;
	this->classId = area->getId();
}

double Neuron::getDensity(){
	return density;
}

int Neuron::getId(){
	return classId;
}

int Neuron::getCountSignals(){
	return winerTimesCount;
}

int Neuron::getDim(){
	return dimentionSize;
}

Cluster * Neuron::getCluster(){
	return area;
}

void Neuron::remove(){
	delete area;
	delete this;
}
