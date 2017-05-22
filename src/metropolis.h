#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float H, float J, float *pE, int *pM, FILE *f);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int idx, float H, float J, float *pE, int *pM, FILE *f);
int imprimir(int *lattice, int n);
int energia(int *lattice, int n, float H, float J);
int magnetizacion(int *lattice,int n);
int CPC(int *lattice, int n, int i, int j, int* spinborde);
#endif
