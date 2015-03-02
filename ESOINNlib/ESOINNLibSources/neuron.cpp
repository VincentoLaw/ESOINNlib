#include "neuron.h"
#include "cluster.h"
#include "connection.h"
#include <iostream>
#include <QString>

Neuron::Neuron(int dimentionSize, double * weights = NULL)
{
        srand((unsigned)time(NULL));
        this->dimentionSize = dimentionSize;
        this->weights = new double[dimentionSize];
        for (int i = 0; i < dimentionSize; i++)
		{
            //TODO: in what borders random values?
            if (weights == NULL)
                this->weights[i] = rand() % 1000;
            else this->weights[i] = weights[i];
        }
        this->area = nullptr;
        this->classId = -1;
        this->density = 0;
        this->winerTimesCount = 0;
        this->point = 0;
        this->winInThisIter = false;
        this->allTimeWin = 0;
}

Neuron::Neuron(vertex v)
{
    srand((unsigned)time(NULL));
    this->dimentionSize = v->getDim();
    this->weights = new double[dimentionSize];
    for (int i = 0; i < dimentionSize; i++)
	{
        //TODO: in what borders random values?
        if (v->weights == NULL)
        this->weights[i] = rand() % 1000;
        else this->weights[i] = v->weights[i];
    }
    this->area = v->getCluster();
    this->classId = v->getId();
    this->density = v->getDensity();
    this->winerTimesCount = v->getCountSignals();
    this->point = 0;
    this->winInThisIter = false;
    this->allTimeWin = 0;
}

Neuron::~Neuron()
{
    //for(auto it = neighboursList->begin(); it != neighboursList->end(); ++it) delete (*it);
    //delete area;
    //cout << "deleted" << endl;
    delete[] weights;
}

void Neuron::incSignal()
{
	winerTimesCount++;
    if (!winInThisIter){
        winInThisIter = true;
        allTimeWin++;
    }
}

void Neuron::setId(int data)
{
	classId = data;
}

void Neuron::setDensity(double data)
{
    this->density = data;
}

cluster Neuron::setArea(cluster buf)
{
	this->area = buf;
	this->classId = area->getId();
    return buf;
}

string Neuron::getNeuronData(){
    QString data = "";
    data += QString::number(similarityThreshold) + " ";
    data += QString::number(point) + " ";
    data += QString::number(winInThisIter) + " ";
    data += QString::number(allTimeWin) + " ";
    data += QString::number(density) + " ";
    data += QString::number(classId) + " ";
    data += QString::number(winerTimesCount);
    return data.toStdString();
}

double Neuron::getDensity()
{
	return density;
}

int Neuron::getId()
{
	return classId;
}

int Neuron::getCountSignals()
{
	return winerTimesCount;
}

int Neuron::getDim()
{
	return dimentionSize;
}

cluster Neuron::getCluster()
{
	return area;
}
