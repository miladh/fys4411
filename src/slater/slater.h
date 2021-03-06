#ifndef SLATER_H
#define SLATER_H

#include <armadillo>
#include <iostream>
#include <libconfig.h++>
#include <src/Jastrow/jastrow.h>
#include <src/Orbitals/orbitals.h>
#include <src/Orbitals/hydrogenic.h>
#include <src/Orbitals/diatomic.h>

using namespace arma;
using namespace std;
using namespace libconfig;

class Slater
{
public:
    Slater(const uint &nParticles, Orbitals *orbitals);


    void initializeSD(const mat &r);
    double evaluateSD(const mat &r);
    void setActiveParticleAndCurrentPosition(const mat &r, uint i );
    void acceptMove();
    void rejectMove();
    void updateSlater();
    double getSDRatio();
    void updateSlaterInverse();

    rowvec gradientSDEvaluate(const mat &r, uint &p);
    double laplaceSDEvaluate(const mat &r, const uint &i);
    double getVariationalDerivate(const mat &r);

private:
    Orbitals* orbitals;
    uint N;
    uint nParticles;
    uint activeParticle;
    double initialSD;
    mat DUp,DDown;
    mat DUpNew, DDownNew;
    mat DUpInv, DDownInv;
    mat DUpInvNew,DDownInvNew;
    mat rNew;


    mat dSD;
    double ddSD, dVSD;
    double R;
    rowvec S ;
};

#endif // SLATER_H
