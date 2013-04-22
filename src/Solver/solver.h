#ifndef VMCSOLVER_H
#define VMCSOLVER_H

#include <armadillo>
#include <iostream>
#include <libconfig.h++>
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <mpi.h>
// Enable warnings again
#pragma GCC diagnostic warning "-Wunused-parameter"

#include <src/includes/lib.h>
#include <src/Wavefunction/wavefunction.h>
#include <src/Hamiltonian/hamiltonian.h>
#include <src/Potential/potential.h>
#include <src/Kinetic/kinetic.h>
#include <src/includes/Defines.h>
#include <src/Observables/observables.h>

using namespace arma;
using namespace std;
using namespace libconfig;


class Solver
{
public:
    Solver(Hamiltonian *hamiltonian, Wavefunction *TrialWavefunction, Observables* observables);
    virtual void solve(int nCycles, long idum) = 0;
    void loadConfiguration(Config *cfg);
    void initializeSolver();

    double acceptedSteps;


protected:
    int nParticles,nDimensions;
    double thermalization,nPreCycles;
    double minStepLength, maxStepLength, tolerance;
    double R;
    mat rOld, rNew;
    Hamiltonian* hamiltonian;
    Wavefunction* TrialWavefunction;
    Observables* observables;

    mat energyVector;

};

#endif // VMCSOLVER_H
