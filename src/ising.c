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
  int n = 32;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;                      //prob de llenado 
  float T = 1.5;                         //temperatura
  float B=(float)1/(float)T;             //beta
  float H=0;                             //campo magnetico
  float J=1;                             //interaccion
  int ter=10000;                         //pasos de termalizacion
  int niter =20000;                    //pasos metropoli
  float E;                               //energia
  int M;                                 //magnetizacion
  float *ecorr= malloc(niter*sizeof(float)); //Ecorrelacion
  int contador;         //Va a contar la cantidad de pasos que acepto
  
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

  //Termalizacion
  for (int i = 0; i < ter; i++)
     {
       metropolis(lattice, n, T, H, J, &E, &M);
     };
  
  
  //Imprimo datos en archivo de texto
   char filename[64];

   FILE *f;                                 // Declara puntero a tipo FILE
   sprintf(filename, "%.2f-%.2f.txt", T,H); // el archivo tiene la temp y el campo
   f=fopen(filename,"wt");
   fprintf(f," Energia\tMagnetizacion\n");
   fprintf(f,"%8.3f\t%8f\n",(float)E/(n*n),(float)M/(n*n));          //aca imprimo los iniciales Eo y Mo

   //Metropolis
   for (int i = 0; i < niter; i++)
     {
       metropolis(lattice, n, T, H, J, &E, &M);
       ecorr[i]=(float)E/(n*n);
       fprintf(f,"%8.3f\t%8.3f\n",(float)E/(n*n),(float)(M)/(n*n)); 
     };
   
   fflush(f);
   fclose(f);
   
   imprimir(lattice,n);

   //Funcion correlacion:
   contador=niter;
   correlacion(ecorr,contador,T,H);
  
  free(lattice);
  free(tabla);
  free(tabla2);
  free(ecorr);
  return 0;
}
