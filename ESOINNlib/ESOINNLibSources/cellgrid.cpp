#include "cellgrid.h"
#include <QString>
#include <cmath>

CellGrid::CellGrid(int dimentionsCount)
{
    dimention_cnt = dimentionsCount;
}

CellGrid::~CellGrid()
{

}

void CellGrid::addPoint(Neuron * neuron){
    QString coords = "";
    for (int i = 0; i < dimention_cnt; i++)
        coords += QString::number(round(neuron->weights[i])) + ", ";
    std::map<string,list<Neuron *> *>::iterator it = grid.find(coords.toStdString());
    if (it == grid.end()){
        list<Neuron *> * l = new list<Neuron *>();
        l->push_back(neuron);
        grid.insert(coords.toStdString(), l);
    }
    else it->second.push(neuron);
}

Neuron * CellGrid::findWinners(double * input_vector, Neuron *&winner, Neuron *&second_winner){
    QString coords = "";
    for (int i = 0; i < dimention_cnt; i++)
        coords += QString::number(round(input_vector)) + ", ";

}
