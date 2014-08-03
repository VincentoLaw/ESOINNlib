#include "connection.h"

Connection::Connection(neuron * first, neuron * second){
    this.first = first;
    this.second = second;
    this::count++;
    this.id = this::count;
    
}

void Connection::increaseAge(int n = 1){
	this.age += n;
}

void Connection::setAge(int age){
	this.age = age;
}

int Connection::getId(){
	return this.age;
}
