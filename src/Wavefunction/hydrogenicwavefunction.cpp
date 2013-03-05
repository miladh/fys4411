#include "hydrogenicwavefunction.h"

HydrogenicWavefunction::HydrogenicWavefunction(const uint &nParticles,const int &charge):
    Wavefunction(nParticles),
    charge(charge),
    nFactor(4*pow((charge/sqrt(4*acos(-1))),3))
{
}

/************************************************************
Name:               HydrogenicWavefunction
Description:        hydrogen like wavefunction
*/

double HydrogenicWavefunction::wavefunction(const mat &r)
{
    TrialWavefunction=slater->initializeSD(r);
    return nFactor*TrialWavefunction;

}



/************************************************************
Name:          Gradient
Description:
*/
mat HydrogenicWavefunction::gradient(const mat &r){


    if(useAnalyticGradient){
        for (uint i = 0; i < r.n_rows; i++){
            for (uint qNum = 0; qNum < r.n_rows/2; qNum++){
                dwavefunction.row(i)=orbitals->gradientOrbitalEvaluate(r,qNum,i);
            }
        }
        return dwavefunction;
    }
    else{
        return gradientNumerical(r);
    }
}


/************************************************************
Name:          laplace
Description:
*/
double HydrogenicWavefunction::laplace(const mat &r){

    if(useAnalyticLaplace){
        ddwavefunction = 0;
        for (uint i = 0; i < r.n_rows; i++){
            for (uint qNum = 0; qNum < r.n_rows/2; qNum++){
                ddwavefunction += orbitals->laplaceOrbitalEvaluate(r,qNum,i); //*SlaterInv(j, i)
            }
        }
        return ddwavefunction;
    }
    else{
        return laplaceNumerical(r);
    }

}




