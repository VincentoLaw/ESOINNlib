#include "neuron.h"
#include <stdlib.h>
#include <time.h>

Neuron::Neuron(int dimentionSize, double * weights = NULL){
        srand(time(NULL));
        this->dimentionSize = dimentionSize;
        if (weights == NULL){
            for (int i = 0; i < dimentionSize; i++){
                //TODO: in what borders random values?
                this->weights[i] = rand() % 1000;
            }
        }
}

void Neuron::incSignal(){
	this->winerTimesCount++;
}

void Neuron::setDensity(int data){
	this->density = data;
}

double Neuron::getDensity(){
	return this->density;
}

int Neuron::getId(){
	return this->classId;
}

int Neuron::getCountSignals(){
	return this->winerTimesCount;
}

int Neuron::getDim(){
	return this->dimentionSize;
}