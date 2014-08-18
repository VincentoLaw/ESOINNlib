#include "connection.h"
#include "neuron.h"

Connection::Connection(Neuron * first, Neuron * second){
    this->first = first;
    this->second = second;
    count++;
    this->id = count;
}		  
void Connection::increaseAge(int n = 1){
	this->age += n;
}

void Connection::setAge(int age){
	this->age = age;
}

int Connection::getId(){
	return this->id;
}

int Connection::getAge(){
	return this->age;
}

Neuron* Connection::getNeighbourNeuron(){
	return this->first == this ? this->second : this->first; 
}
