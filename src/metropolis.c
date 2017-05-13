#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "metropolis.h"

int metropolis(int *lattice, int n, float T) {
  //Calculo la energia Eo=E(s)
  int E=0;
  int J=-1; //interaccion
  for (int i=0;i<n;i++)
    {
    for (int j=0;j<n;j++)
      {
        //Esta forma de definir los j y los i arregla el problema de las
        //condiciones periodicas de contorno, evitando usar ifs:
      
         int  jl=(j-1+n)%n;  //j_ izq
         int  jr=(j+1+n)%n;  //j_dcha
         int  iu=(i-1+n)%n;  //i_arriba
         int  id=(i+1+n)%n;  //i_abajo

         int  sij=lattice[i*n+j]; //el actual 
     
         int  sr=lattice[i*n+jr];
         int  sl=lattice[i*n+jl];
         int  su=lattice[iu*n+j];
         int  sd=lattice[id*n+j];

         E=E+J*((sij*su)+(sij*sd)+(sij*sl)+(sij*sr));
      }
    }
  //Imprimo la energia
  printf("Energia=%d\n",E/2); //se divide por dos porque en la suma cuento dos
                              // veces el mismo par
  
  //Elijo spin random

  //Calculo la energia E(-s)

  //Calculo Beta.DeltaT
  
 return 0;
}

int pick_site(int *lattice, int n) {
  int j;
  int idx; //idx es la posicion del vector lattice que voy a  flipear( 1< idx< n*n)
  idx =(int)((float)rand()*n*n/(float)RAND_MAX);
  printf("%d\n",idx);
  return idx;
}

int flip(int *lattice, int n, float T, int idx) {
  lattice[idx]=lattice[idx]*(-1);
  return 0;
}
