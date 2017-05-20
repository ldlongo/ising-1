#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "metropolis.h"
#include "lattice.h"
#include <math.h>


float *lut;  //esta variable será global puntero a tabla1
float *lut2; //esta variable será global puntero a tabla2

int main(int argc, char **argv) {
  int n = 16;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;           //prob de llenado 
  float T = 3.0;              //temperatura
  float B=(float)1/(float)T;  //beta
  float H=0;                  //campo magnetico
  float J=1;                  //interaccion
  int niter =5000;            //pasos metropoli
  float E;                    //energia
  int M;                      //magnetizacion
  //---------------------------------------
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
  //-------------------------------------
  //Tabla2
  //+-2H vs exp(-+2H)
  float *tabla2=malloc(2*sizeof(float));
  for(int i=0;i<2;i++){
    tabla2[i]=(-1+2*i)*2*H;
    tabla2[i+2]=pow(exp(1.),-(-1+2*i)*(2*H));
  }
  lut2=tabla2;
  //-------------------------------------
  
  srand(time(NULL));
 
  fill_lattice(lattice, n, prob);
  
  E=energia(lattice,n,H, J);
  
  M=magnetizacion(lattice,n);
  
  printf("Eo:%.3f ",E);
  printf("Mo:%d\n",M);
  
  //Imprimo datos en archivo de texto
   char filename[64];

   FILE *f;                                 // Declara puntero a tipo FILE
   sprintf(filename, "%.2f-%.2f.txt", T,H); // el archivo tiene la temp y el campo
   f=fopen(filename,"wt");
   fprintf(f," Energia\tMagnetizacion\n");
   fprintf(f,"%8.3f\t%8d\n",E,M);          //aca imprimo los iniciales Eo y Mo
  
   for (int i = 0; i < niter; i++)
     {
       metropolis(lattice, n, T, H, J, &E, &M);
       //En terminal
         printf("E:%.3f ",E);
         printf("M:%d\n",M);
       //En archivo externo
         fprintf(f,"%8.3f\t%8d\n",E,M);
     };

   fflush(f);
   fclose(f);
   
  imprimir(lattice,n); 
  free(lattice);
  free(tabla);
  return 0;
}
