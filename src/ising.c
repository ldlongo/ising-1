#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "metropolis.h"
#include "lattice.h"
#include <math.h>

float *lut; //esta variable será global.

int main(int argc, char **argv) {
  int n = 4;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.1;
  float T = 3.0;
  float B=(float)1/(float)T;
  int niter = 2000;
  int idx;

  //Tabla DeltaE vs exp(-BDeltaE)
  extern float *lut;
  float *tabla=malloc(10*sizeof(float));
  for (int i=0;i<5;i++){
    tabla[i]=-8+4*i;
    tabla[i+5]=pow(exp(1.),-B*(-8+4*i));
  }
  lut=tabla;
  
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
   for (int i = 0; i < niter; i++)
     {
       metropolis(lattice, n, T);
     };
  free(lattice);
  free(tabla);
  return 0;
}
