#ifndef VMCAPP_H
#define VMCAPP_H


#include <armadillo>
#include <iostream>
#include <libconfig.h++>
#include "src/VMCSolver/vmcsolver.h"
#include "src/Wavefunction/wavefunction.h"
#include "src/Hamiltonian/hamiltonian.h"

using namespace arma;
using namespace std;
using namespace libconfig;

class VMCApp
{
public:
    VMCApp();

    VMCSolver* vmcsolver;
    Wavefunction *TrialWaveFunction;
    Potential *potential;
    Kinetic *kinetic;
    Hamiltonian *hamiltonian;

    int nDimensions,nParticles,nCycles,charge;
    double stepLength,h,h2;
    double alpha, beta;
    long idum;


    mat rOld;
    mat rNew;

    void run();
};

#endif // VMCAPP_H