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
  int n;
  float prob = 0.5;                      //prob de llenado 
  float T;                               //temperatura
  float B;                               //beta
  float H=0;                             //campo magnetico
  float J;                             //interaccion ferro primeros vecinos
  float K=-1;                          //interaccion antiferro diagonal
  int ter=10000;                         //pasos de termalizacion
  int niter=1000000;                    //pasos metropoli
  float E;                               //Energia
  int M;                                 //Magnetizacion
  float E2prom;                          //Energia al cuadrado promedio
  float enerprom;                         //energia promedio por nodo
  float M2prom;                          //Magnetizacion al cuadrado promedio
  float magnprom;                        //magnetizacion promedio por nodo
  float enerdisp;                        //error en la energia prom
  float magndisp;                        //error en la magn prom
  float cv;                              //calor especifico
  float suscep;                          //susceptibilidad
  int contador;
  //float *e= malloc(niter*sizeof(float)); //energia por nodo
  //float *m=malloc(niter*sizeof(float));   //magnetiz por nodo
  
  //float *tabla=malloc(10*sizeof(float));
  //float *tabla2=malloc(2*sizeof(float));
  
  //Lleno temp e imprimo en archivo externo temp.txt
  char filename[64];
  FILE *h;
  sprintf(filename, "temp.txt");
  h=fopen(filename,"wt");
  fprintf(h,"Temperaturas\n");
  
  float ts=5.5;    //temp sup
  float ti=0.5;  //temp inf
  int numtemp=5;  //cant de temp
  float paso=(float) (ts-ti)/numtemp;//numtemp;
  float *temp=malloc(numtemp*sizeof(float));
 
  for(int t=0;t<numtemp;t++){
    temp[t]=ts-paso*t;
    fprintf(h,"%f\n",temp[t]);
  }
  fflush(h);
  fclose(h);

  //Lleno tamano e imprimo en archivo externo tamano.txt
  sprintf(filename, "tamano.txt");
  h=fopen(filename,"wt");
  fprintf(h,"Tamanos\n");
  
  int ns=16;    //tamano sup
  int numtamano=1;  //cant de tamanos
  int *tamano=malloc(numtamano*sizeof(int));
 
  for(int x=0;x<numtamano;x++){
    tamano[x]=(int)ns/pow(2,x);
    fprintf(h,"%d\n",tamano[x]);
  }
  fflush(h);
  fclose(h);

  //Lleno j acople e imprimo en archivo acople.txt
  sprintf(filename, "acople.txt");
  h=fopen(filename,"wt");
  fprintf(h,"Acople J\n");
  
  float js=1;    //j sup
  float ji=1;  //j inf
  int numacople=1;  //cant de j
  float pasoacople=(float) (js-ji)/numacople;//numacople;
  float *acople=malloc(numacople*sizeof(float));
 
  for(int t=0;t<numacople;t++){
    acople[t]=js-pasoacople*t;
    fprintf(h,"%f\n",acople[t]);
  }
  fflush(h);
  fclose(h);

  
  //Archivo donde imprimo temp vs magnprom
  // char filename[64];
  //sprintf(filename, "M-T-%d-%f.txt",n,J); // el archivo tiene la temp
  // h=fopen(filename,"wt");
  //fprintf(h,"T\t<m>\td<m>\n");

  //Archivo donde imprimo temp s energiaprom
  //FILE *k;
  //sprintf(filename,"E-T-%d-%f.txt",n,J);
  //k=fopen(filename,"wt");
  //fprintf(k,"T\t<e>\td<e>\n");

  //Lleno la red una sola vez
  // srand(time(NULL));
  // fill_lattice(lattice, n, prob);
  int x;
  int z;
  int t;
  int i;
  FILE *f;// Declara puntero a tipo FILE
  FILE *k;
  
 //Recorro tamano:
 for (x=0;x<numtamano;x++){
  n=tamano[x];
  int *lattice = malloc(n * n * sizeof(int));
  //Lleno la red una sola vez
   srand(time(NULL));
   fill_lattice(lattice, n, prob);
  //float *e=malloc(niter*sizeof(float)); //energia por nodo
  //float *m=malloc(niter*sizeof(float));   //magnetiz por nodo
  // float *tabla=malloc(10*sizeof(float));
  //float *tabla2=malloc(2*sizeof(float));
   
 //Recorro acople:
 for (z=0;z<numacople;z++){
   J=acople[z];

 //Archivo donde imprimo temp s energiaprom
  sprintf(filename,"E-T-%d-%0.2f.txt",n,J);
  k=fopen(filename,"wt");
  fprintf(k,"T\t<e>\td<e>\tcv\n");

 //Archivo donde imprimo temp vs magnprom
  sprintf(filename, "M-T-%d-%0.2f.txt",n,J); // el archivo tiene la temp
  h=fopen(filename,"wt");
  fprintf(h,"T\t<m>\td<m>\tsuscep\n");
      
 //Recorro temp:
 for (t=0;t<numtemp;t++){
  T=temp[t]; 
  B=(float)1/(float)T;
  float *e=malloc(niter*sizeof(float)); //energia por nodo
  float *E2=malloc(niter*sizeof(float));//energia al cuadrado
  float *m=malloc(niter*sizeof(float));   //magnetiz por nodo
  float *M2=malloc(niter*sizeof(float));  //magnetiz al cuadrado
  float *tabla=malloc(10*sizeof(float));
  float *tabla2=malloc(2*sizeof(float));
    
  //---------------------------------------
  //Tabla1
  //DeltaE vs exp(-BDeltaE)
  extern float *lut;
  extern float *lut2;
  
  for (i=0;i<5;i++){
    tabla[i]=-8+4*i;
    tabla[i+5]=pow(exp(1.),-B*(-8+4*i));
   }
   lut=tabla;
  //-------------------------------------
  //Tabla2
  //+-2H vs exp(-+2H)
  
  for(i=0;i<2;i++){
    tabla2[i]=(-1+2*i)*2*H;
    tabla2[i+2]=pow(exp(1.),(-B)*(-1+2*i)*(2*H));
  }
  lut2=tabla2;

  //Imprimo la tabla 2
  //for (int i=0;i<2;i++){
  //  printf("%f\t%f\n",tabla2[i],tabla2[i+2]);
  //}
  //-------------------------------------
  
  //Lleno la red en cada temp
  // srand(time(NULL));
  //fill_lattice(lattice, n, prob);
  
  E=energia(lattice,n, H, J, K);
  
  M=magnetizacion(lattice,n);

  // Termalizacion
   for (i = 0; i < ter; i++)
   {
     metropolis(lattice, n, T, H, J, K, &E, &M);
   };    
  
  //Imprimo datos en archivo de texto

   //Imprimo todos los e y m de cada paso metropolis                                
   //sprintf(filename, "%d-%.2f-%.2f.txt",n,T,J); // el archivo tiene la temp y el acople J
   // f=fopen(filename,"wt");
   //fprintf(f," Energia\tMagnetizacion\n");
   // fprintf(f,"%8.3f\t%8.3f\n",(float)E/(n*n),(float)M/(n*n));          //aca imprimo los iniciales Eo y Mo

   //Metropolis
   for (i = 0; i < niter; i++)
     {
       metropolis(lattice, n, T, H, J, K, &E, &M);
       e[i]=(float)E/(n*n);
       E2[i]=(float)(E*E);
       m[i]=(float)M/(n*n);
       M2[i]=(float)(M*M);
       //fprintf(f,"%8.3f\t%8.3f\n",(float)E/(n*n),(float)(M)/(n*n)); 
     };
   
   //fflush(f);
   //fclose(f);

   //Imprimo red
   imprimir(lattice,n);

   //Temp
   printf("T:%f ",temp[t]);
   
   //Promedio Energia
   E2prom=promedio(E2,n,niter)[0];
   enerprom=promedio(e,n,niter)[0];
   enerdisp=promedio(e,n,niter)[1];
   cv=(E2prom-(enerprom*enerprom*n*n*n*n))/(T*T*n*n);
   printf("<e>:%f d<e>:%f ",enerprom,enerdisp);
   
   fprintf(k,"%4.3f\t%4.3f\t%4.3f\t%4.3f\n",T,enerprom,enerdisp,cv);

   //Promedio Magnetizacion
   M2prom=promedio(M2,n,niter)[0];
   magnprom=promedio(m,n,niter)[0];
   magndisp=promedio(m,n,niter)[1];
   suscep=(M2prom-(magnprom*magnprom*n*n*n*n))/(T);
   printf("<m>:%f d<m>:%f\n ",magnprom,magndisp);

   fprintf(h,"%4.3f\t%4.3f\t%4.3f\t%4.3f\n",temp[t],magnprom,magndisp,suscep);

   //Funcion correlacion:
   //contador=niter;
   //correlacion(e,contador,n,T,H,J);

  
  free(tabla);
  free(tabla2);

  free(e);
  free(m);
  free(E2);
  free(M2);
   }
      
   fflush(k);
   fclose(k);

   fflush(h);
   fclose(h);
  }
 free(lattice);
 }
free(tamano);
free(temp);
free(acople);
return 0;
}
