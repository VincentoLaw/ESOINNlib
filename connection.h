#pragma once
#include "neuron.h"

class Neuron;

//Also can be called as edge
class Connection{
    private:
        int age;
        int id;
        static int count = 0;
    public:
        Neuron * first, * second;

        Connection(Neuron * first, Neuron * second);
        //increasing age of connection by n
        void increaseAge(int n = 1);
        void setAge();
        int getId();
};
