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


void Neuron::incSignal(int n = 1){
	this.winnerTimesCount += n;
}

void Neuron::setDensity(int data){
	this.density = data;
}
