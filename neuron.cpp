#include "neuron.h"
#include <stdlib.h>
#include <time.h>

Neuron::Neuron(int dimentionSize, double * values = NULL){
        srand(time(NULL));
        this->dimentionSize = dimentionSize;
        if (values == NULL){
            for (int i = 0; i < dimentionSize; i++){
                //TODO: in what borders random values?
                this->values[i] = rand() % 1000;
            }
        }
}
