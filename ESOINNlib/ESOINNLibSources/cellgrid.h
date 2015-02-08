#ifndef CELLGRID_H
#define CELLGRID_H
#include <list>
#include <ESOINNLibSources/neuron.h>
#include <map>

class CellGrid
{
private:
    int dimention_cnt;
public:
    //list<Neuron> outside_neurons;
    map<string, list<Neuron *> *> grid;
    void addPoint(Neuron * neuron);
    Neuron * findWinners(double * input_vector, Neuron *&winner, Neuron *&second_winner);
    CellGrid(int dimentionsCount);
    ~CellGrid();
};

#endif // CELLGRID_H
