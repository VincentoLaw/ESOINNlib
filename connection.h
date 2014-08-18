#pragma once
#include "neuron.h"

//Also can be called as edge
class Connection {
    
	private:
        
		int age;
        int id;
        static int count;
    
	public:
      	
		Connection(Neuron * first, Neuron * second)
		Neuron * first, * second;
        //increasing age of connection by n
        void incAge();
        Neuron* getNeighbourNeuron(Neuron* node);
        void setAge(int age);
        int getId();
        int getAge();
};
