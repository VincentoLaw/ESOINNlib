#include "neuron.h"
#include "esoinn.h"

Esoinn::Esoinn(int inputSize, double learningRate, int maximalConnectionAge, int lambda, double (*distanceFunction)(double *,double *)){//= &commonDistanceFunction
    this->inputSize = inputSize;
    neuronsList = new std::list<Neuron>();
}

//TODO: implement this function
void Esoinn::inputSignal(double * inputVector){
}

//This main function for testing. When we will make lib it will be removed.
int main(){
}
