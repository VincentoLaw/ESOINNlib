#pragma once

#include <memory>
#define vertex shared_ptr<Neuron>


//Also can be called as edge

using namespace std;

class Neuron;

class Connection
{

	private:

		int age;

	public:

        Connection(vertex first, vertex second);
		~Connection();
        vertex first;
        vertex second;
        void incAge();
        vertex getNeighbourNeuron(vertex node);
        void setAge(int age);
        int getAge();
};

