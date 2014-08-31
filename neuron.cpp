#include "neuron.h"
#include <stdlib.h>
#include <time.h>

Neuron::Neuron(int dimentionSize, double * weights = NULL){
        srand(time(NULL));
        this->dimentionSize = dimentionSize;
        if (weights == NULL){
            for (int i = 0; i < dimentionSize; i++){
                //TODO: in what borders random values?
                weights[i] = rand() % 1000;
            }
        }
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