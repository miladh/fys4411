#ifndef POTENTIAL_H
#define POTENTIAL_H

#include <armadillo>
#include <iostream>
#include <libconfig.h++>

using namespace arma;
using namespace std;
using namespace libconfig;


class Potential
{
public:
    Potential();
    virtual double evaluate(int nParticles,const mat &r) = 0;
    Config *cfg;
};

#endif // POTENTIAL_H
