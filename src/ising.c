#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "metropolis.h"
#include "lattice.h"
#include <math.h>


float *lut; //esta variable será global.
float *lut2; //esta variable será global.

int main(int argc, char **argv) {
  int n = 16;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 3.0;              //temperatura
  float B=(float)1/(float)T;
  float H=0;                  //campo magnetico
  int niter =100;
  int idx;
  float E;
  int M;

  //Tabla1
  //DeltaE vs exp(-BDeltaE)
  extern float *lut;
  extern float *lut2;
  
  float *tabla=malloc(10*sizeof(float));
  for (int i=0;i<5;i++){
    tabla[i]=-8+4*i;
    tabla[i+5]=pow(exp(1.),-B*(-8+4*i));
  }
  lut=tabla;
  //Tabla2
  //+-2H vs exp(-+2H)
  float *tabla2=malloc(2*sizeof(float));
  for(int i=0;i<2;i++){
    tabla2[i]=(-1+2*i)*2*H;
    tabla2[i+2]=pow(exp(1.),-(-1+2*i)*(2*H));
  }
  lut2=tabla2;
  
  srand(time(NULL));
  
  fill_lattice(lattice, n, prob);

  imprimir(lattice,n);
  E=energia(lattice,n,H);
  M=magnetizacion(lattice,n);
  printf("Eo:%.3f ",E);
  printf("Mo:%d\n",M);
  
   for (int i = 0; i < niter; i++)
     {
       metropolis(lattice, n, T, H, &E, &M);
       printf("E:%.3f ",E);
       printf("M:%d\n",M);
     };
  imprimir(lattice,n); 
  free(lattice);
  free(tabla);
  return 0;
}
