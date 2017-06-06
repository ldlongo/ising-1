#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float H, float J, float K,float *pE, int *pM);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int idx, float H, float J, float K,float *pE, int *pM);
int imprimir(int *lattice, int n);
int energia(int *lattice, int n, float H, float J, float K);
int magnetizacion(int *lattice,int n);
int CPC(int *lattice, int n, int i, int j, int* spinborde);
int correlacion(float *e, int contador, int n,float T, float H, float J);
float *promedio(float *a, int n, int niter);
#endif

