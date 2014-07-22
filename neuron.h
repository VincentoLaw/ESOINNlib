#pragma once

class Neuron{
    double density;
    double similarityThreshold;
    int dimentionSize;
    int classId;
    double * values;
public:
    Neuron(int dimentionSize, double * values);
    void updateDensity();
};
