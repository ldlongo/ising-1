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
  float T;                               //temperatura
  float B;                               //beta
  float H=0;                             //campo magnetico
  float J=1;                             //interaccion
  int ter=5000;                         //pasos de termalizacion
  int niter=1000000;                    //pasos metropoli
  float E;                               //Energia
  int M;                                 //Magnetizacion
  float *e= malloc(niter*sizeof(float)); //energia por nodo
  float *m=malloc(niter*sizeof(float));   //magnetiz por nodo
  float enerprom;                         //energia promedio por nodo
  float magnprom;                        //magnetizacion promedio por nodo
  int contador;                     
  
  float *tabla=malloc(10*sizeof(float));
  float *tabla2=malloc(2*sizeof(float));

  //Lleno temp e imprimo en archivo externo temp.txt
  char filename[64];
  FILE *h;
  sprintf(filename, "temp.txt");
  h=fopen(filename,"wt");
  fprintf(h,"Temperaturas\n");
  
  float ts=3;    //temp sup
  float ti=0.5;  //temp inf
  int numtemp=6;  //cant de temp
  float paso=(float) (ts-ti)/numtemp;//numtemp;
  float *temp=malloc(numtemp*sizeof(float));
 
  for(int t=0;t<numtemp;t++){
    temp[t]=ts-paso*t;
    fprintf(h,"%f\n",temp[t]);
  }
  fflush(h);
  fclose(h);

  
  //Archivo donde imprimo temp vs magnprom
  // char filename[64];
  sprintf(filename, "M-T.txt"); // el archivo tiene la temp
  h=fopen(filename,"wt");

  //Lleno la red una sola vez
  srand(time(NULL));
  
  fill_lattice(lattice, n, prob);
  
  //Recorro temp:
  for (int t=0;t<numtemp;t++){
    T=temp[t];
    B=(float)1/(float)T; 
    
  //---------------------------------------
  //Tabla1
  //DeltaE vs exp(-BDeltaE)
  extern float *lut;
  extern float *lut2;
  
  for (int i=0;i<5;i++){
    tabla[i]=-8+4*i;
    tabla[i+5]=pow(exp(1.),-B*(-8+4*i));
  }
  lut=tabla;
  //-------------------------------------
  //Tabla2
  //+-2H vs exp(-+2H)
  
  for(int i=0;i<2;i++){
    tabla2[i]=(-1+2*i)*2*H;
    tabla2[i+2]=pow(exp(1.),-(-1+2*i)*(2*H));
  }
  lut2=tabla2;
  //------------------------------------- 
  
  E=energia(lattice,n, H, J);
  
  M=magnetizacion(lattice,n);

  // Termalizacion
   for (int i = 0; i < ter; i++)
   {
   metropolis(lattice, n, T, H, J, &E, &M);
   };    
  
  //Imprimo datos en archivo de texto

   FILE *f;                                 // Declara puntero a tipo FILE
   sprintf(filename, "%.2f.txt", T); // el archivo tiene la temp
   f=fopen(filename,"wt");
   fprintf(f," Energia\tMagnetizacion\n");
   fprintf(f,"%8.3f\t%8f\n",(float)E/(n*n),(float)M/(n*n));          //aca imprimo los iniciales Eo y Mo

   //Metropolis
   for (int i = 0; i < niter; i++)
     {
       metropolis(lattice, n, T, H, J, &E, &M);
       e[i]=(float)E/(n*n);
       m[i]=(float)M/(n*n);
       fprintf(f,"%8.3f\t%8.3f\n",(float)E/(n*n),(float)(M)/(n*n)); 
     };
   
   fflush(f);
   fclose(f);

   //Imprimo red
   imprimir(lattice,n);

   //Temp
   printf("T:%f ",temp[t]);
   
   //Promedio Energia
   enerprom=promedio(e,niter);
   printf("<e>:%f ",enerprom);

   //Promedio Magnetizacion
   magnprom=fabs(promedio(m,niter));
   printf("<m>:%f\n ",magnprom);

   fprintf(h,"%8.3f\t%8.3f\n",temp[t],magnprom);

   //Funcion correlacion:
    contador=niter;
    correlacion(e,contador,T,H);
  }

  fflush(h);
  fclose(h);
  
  free(lattice);
  free(tabla);
  free(tabla2);
  free(e);
  free(m);
  free(temp);
  
  return 0;
}
