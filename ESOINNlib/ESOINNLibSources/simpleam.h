#ifndef SIMPLEAM_H
#define SIMPLEAM_H
#include "ESOINNLibSources/esoinn.h"

class SimpleAM
{
public:
    SimpleAM(list<Esoinn> senses);
    ~SimpleAM();
    Esoinn * senses;
    void learn(list<double*> inputs);
    bool classify();
    int * getAssotiations();
};

#endif // SIMPLEAM_H
