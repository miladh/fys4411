#ifndef DEFINES_H
#define DEFINES_H


#define hGrad 1e-5
#define h 1e-5
#define h2 1e10


// 0: OBD off
// 1: OBD on
#define ONEBODYDENSITY 0

enum SYSTEM{
   ATOMS, MOLECULES
};

enum TRIALWAVEFUNCTION {
   BASIC,JASTROW
};

enum SOLVER {
   BF, IS
};

enum INTERACTION {
   NOINTERACTION, COULOMBINTERACTION
};


enum MINIMIZER {
   BRUTEFORCE, STEEPESTDESCENT
};
#endif // DEFINES_H
