#pragma once

class Neuron{
    double density;
    int dimentionSize;
    int classId;
public:
    Neuron(int dimentionSize){
        this.dimentionSize = dimentionSize;
    }
    void updateDensity();
};
