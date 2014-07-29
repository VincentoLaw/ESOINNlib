#pragma once
#include "neuron.h"

class Neuron;

//Also can be called as edge
class Connection{
    private:
        int age;
    public:
        Neuron * first, * second;

        Connection(Neuron * first, Neuron * second);
        //increasing age of connection by 1
        void increaseAge();
};
