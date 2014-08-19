#include "connection.h"
#include "neuron.h"

Connection::Connection(Neuron * first, Neuron * second){
    this->first = first;
    this->second = second;
    count++;
    this->id = count;
}
void Connection::incAge(){
	this->age++;
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

Neuron* Connection::getNeighbourNeuron(Neuron *node){
	return this->first == node ? this->second : this->first;
}
