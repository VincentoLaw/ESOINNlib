//#pragma once
#include "neuron.h"


//Also can be called as edge
class Connection {
    
	private:
        
		int age;
        int id;
        static int count;
    
	public:
        
		Neuron * first, * second;

        Connection(Neuron * first, Neuron * second);
        //increasing age of connection by n
        void increaseAge(int n = 1);
        Neuron* getNeighbourNeuron();
        void setAge();
        int getId();
};
