#include "hydrogenic.h"

Hydrogenic::Hydrogenic(double* k):
    k(k)
{
}


//********************************************************************************
double Hydrogenic::orbitalEvaluate(const mat &r, int qNum, int Particle){
    rNorm= norm(r.row(Particle),2);

    if(qNum==0){
        phi= exp(-(*k)*rNorm);
    }
    else if (qNum==1){
        phi = ((*k)*rNorm-2 )*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 2) {
        phi = r(Particle,2)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 3) {
        phi =r(Particle,0)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 4) {
        phi =  r(Particle,1)*exp(-0.5*(*k)*rNorm);
    }
    else if(qNum==5){
        phi= (27 - 18*(*k)*rNorm + 2*(*k)*(*k)*rNorm*rNorm)*
             exp(-(*k)*rNorm/3);
    }
    else{
        cerr << "Orbital doesn't exist!"<<endl;
        exit(1);}

    return phi;
}

//********************************************************************************
rowvec Hydrogenic::gradientOrbitalEvaluate(const mat &r, int qNum, int Particle){
    rNorm= norm(r.row(Particle),2);
    dphi=zeros(1,r.n_cols);

    // 1s orbital
    if(qNum==0){
        dphi= (-(*k)/rNorm)*r.row(Particle)*exp(-(*k)*rNorm);
    }

    // 2s orbital
    else if (qNum==1){
        dphi = (-(*k)/(2*rNorm))*((*k)*rNorm-4)*r.row(Particle)*exp(-0.5*(*k)*rNorm);
    }

    // 2p orbital
    else if (qNum == 2) {
        dphi(0,0) = r(Particle,0)*r(Particle,2);
        dphi(0,1) = r(Particle,1)*r(Particle,2);
        dphi(0,2) = r(Particle,2)*r(Particle,2)-2*rNorm/(*k);
        dphi*= (-(*k)/(2*rNorm))*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 3) {
        dphi(0,0) = r(Particle,0)*r(Particle,0)-2*rNorm/(*k);
        dphi(0,1) = r(Particle,0)*r(Particle,1);
        dphi(0,2) = r(Particle,0)*r(Particle,2);
        dphi*= (-(*k)/(2*rNorm))*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 4) {
        dphi(0,0) = r(Particle,1)*r(Particle,0);
        dphi(0,1) = r(Particle,1)*r(Particle,1)-2*rNorm/(*k);
        dphi(0,2) = r(Particle,1)*r(Particle,2);
        dphi*= (-(*k)/(2*rNorm))*exp(-0.5*(*k)*rNorm);
    }

    // 3s orbital
    else if(qNum==5){
        dphi = -(*k)*r.row(Particle)/(3*rNorm)*
               (2*(*k)*(*k)*rNorm*rNorm-30*(*k)*rNorm+81)*
               exp(-(*k)*rNorm/3);
    }
    else{
        cerr << "Orbital doesn't exist!"<<endl;
        exit(1);
    }

    return dphi;
}
//********************************************************************************
double Hydrogenic::laplaceOrbitalEvaluate(const mat &r, int qNum, int Particle){
    rNorm= norm(r.row(Particle),2);
    if(qNum==0){
        ddphi= (*k)*((*k)*rNorm-2)/rNorm*exp(-(*k)*rNorm);
    }
    else if (qNum==1){
        ddphi = (*k)*((*k)*rNorm-8)*((*k)*rNorm-2)/(4*rNorm)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum==2){
        ddphi = (*k)*((*k)*rNorm-8)/(4*rNorm)*
                r(Particle,2)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum==3){
        ddphi = (*k)*((*k)*rNorm-8)/(4*rNorm)*
                r(Particle,0)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum==4){
        ddphi = (*k)*((*k)*rNorm-8)/(4*rNorm)*
                r(Particle,1)*exp(-0.5*(*k)*rNorm);
    }
    else if(qNum==5){
        ddphi= (*k)*((*k)*rNorm-18)*(2*(*k)*(*k)*rNorm*rNorm
                -18*(*k)*rNorm+27)/(9*rNorm)*exp(-(*k)*rNorm/3);
    }
    else{
        cerr << "Orbital doesn't exist!"<<endl;
        exit(1);
    }

    return ddphi;
}


//********************************************************************************
double Hydrogenic::getVariationalDerivative(const mat &r, int qNum, int Particle){
    rNorm= norm(r.row(Particle),2);

    if(qNum==0){
        dVariational= -rNorm*exp(-(*k)*rNorm);
    }
    else if (qNum==1){
        dVariational = rNorm*(2 - rNorm*(*k)/2)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 2) {
        dVariational = (-0.5*rNorm)*r(Particle,2)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 3) {
        dVariational =(-0.5*rNorm)*r(Particle,0)*exp(-0.5*(*k)*rNorm);
    }
    else if (qNum == 4) {
        dVariational = (-0.5*rNorm)*r(Particle,1)*exp(-0.5*(*k)*rNorm);
    }
    else if(qNum==5){
        dVariational= rNorm*(-27 + 10*rNorm*(*k) - 2* rNorm*rNorm*(*k)*(*k)/3)*
             exp(-(*k)*rNorm/3);
    }
    else{
        cerr << "Orbital doesn't exist!"<<endl;
        exit(1);}

    return dVariational;
}

















