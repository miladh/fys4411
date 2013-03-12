#include "slater.h"
#include "src/Orbitals/hydrogenic.h"

Slater::Slater(const uint &nParticles):
    N(nParticles/2),
    orbitals(new Hydrogenic),
    DUp(zeros(N,N)),
    DDown(zeros(N,N)),
    DUpNew(zeros(N,N)),
    DDownNew(zeros(N,N)),
    DUpInv(zeros(N,N)),
    DDownInv(zeros(N,N)),
    DUpInvNew(zeros(N,N)),
    DDownInvNew(zeros(N,N)),
    rNew(zeros(nParticles,3))

{
}


/************************************************************
Name:
Description:
*/
void Slater::initializeSD(const mat &r){

    evaluateSD(r);
    DUpNew=DUp;
    DDownNew=DDown;

    DUpInv=inv(DUp);
    DDownInv=inv(DDown);

    DUpInvNew=DUpInv;
    DDownInvNew=DDownInv;

}


/************************************************************
Name:
Description:
*/
double Slater::evaluateSD(const mat &r){
    for (uint p = 0; p < N; p++) {
        for (uint qNum = 0; qNum < N; qNum++) {
            DUp(p,qNum) = orbitals->orbitalEvaluate(r,qNum,p);
            DDown(p, qNum) = orbitals->orbitalEvaluate(r,qNum,p+N);
        }
    }

    return det(DUp)*det(DDown);

}

/************************************************************
Name:
Description:
*/
void Slater::setActiveParticleAndCurrentPosition(const mat &r, uint i ){
    activeParticle=i;
    rNew=r;
}

/************************************************************
Name:
Description:
*/
void Slater::updateSlater(){

    if (activeParticle < N) {
         for (uint qNum = 0; qNum  < N; qNum ++) {
             DUpNew(activeParticle, qNum) =orbitals->orbitalEvaluate(rNew,qNum ,activeParticle);
         }
     } else {
         for (uint qNum  = 0; qNum  < N; qNum ++) {
             DDownNew(activeParticle - N, qNum) = orbitals->orbitalEvaluate(rNew,qNum ,activeParticle);
         }
     }

    DUpInvNew=inv(DUpNew);
    DDownInvNew=inv(DDownNew);
}


/************************************************************
Name:
Description:
*/
double Slater::getSDRatio(){
    double R = 0;
    uint i = activeParticle;

     if (i < N) {
         for (uint j = 0; j < N; j++) {
             R += DUpNew(i,j) * DUpInv(j, i);
         }
     } else {
         for (uint j = 0; j < N; j++) {
             R += DDownNew(i - N,j) * DDownInv(j, i - N);
         }
     }
     return R;
}



/************************************************************
Name:
Description:
*/
void Slater::acceptMove(){

    if (activeParticle < N) {
          for (uint i = 0; i < N; i++){
              DUp(activeParticle, i) = DUpNew(activeParticle, i);
          }
          DUpInv = DUpInvNew;
      }
    else {
          for (uint i = 0; i < N; i++){
              DDown(activeParticle - N, i) = DDownNew(activeParticle - N, i);
          }
          DDownInv = DDownInvNew;
      }
}


/************************************************************
Name:
Description:
*/
void Slater::rejectMove(){

    if (activeParticle < N) {
          for (uint i = 0; i < N; i++){
              DUpNew(activeParticle, i) = DUp(activeParticle,i);
          }
          DUpInvNew = DUpInv;
      }
    else {
          for (uint i = 0; i < N; i++){
              DDownNew(activeParticle - N, i) = DDown(activeParticle - N, i);
          }
          DDownInvNew = DDownInv;
      }

}



/************************************************************
Name:               gradientSlater
Description:
*/

rowvec Slater::gradientSDEvaluate(const mat &r, uint &i) {
    dSD= zeros(1, r.n_cols);

    if (i < N) {
        for (uint j = 0; j < N; j++) {
            dSD += orbitals->gradientOrbitalEvaluate(r,j,i) * DUpInvNew(j, i);
        }
    } else {
        for (uint j = 0; j < N; j++) {
            dSD += orbitals->gradientOrbitalEvaluate(r,j,i) * DDownInvNew(j, i - N);
        }
    }
    return dSD;
}


/************************************************************
Name:               laplaceSlater
Description:
*/

double Slater::laplaceSDEvaluate(const mat &r,const uint &i) {
    ddSD = 0;
    if (i < N) {
        for (uint j = 0; j < N; j++) {
            ddSD += orbitals->laplaceOrbitalEvaluate(r,j,i)*DUpInv(j, i);
        }
    } else {
        for (uint j = 0; j < N; j++) {
            ddSD += orbitals->laplaceOrbitalEvaluate(r,j,i)*DDownInv(j, i-N);
        }
    }

    return ddSD;
}


