#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <math.h>
#include <time.h>

float *lut;
float *lut2;
int main(){
  int n=3;
  int *lattice=malloc(n*n*sizeof(int));
  int *hist=malloc(2*n*n*sizeof(int));
  int iter=1000000;
  int idx;
  float T=2.5;
  float B=1/(float)T;
  float H=0;
  int J=1;
  float E=0;
  int M=0;
  int swich=0;
  
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
  //------------------------------------

  //Lleno clase:
  for (int i=0;i<(n*n);i++)
    {
      hist[i]=i;
      hist[(n*n)+i]=0;
    }
  
  //1)Test pick_site:
  for (int i=0; i<iter;i++)
    {
      idx=pick_site(lattice, n);
      //Lo clasifico
      hist[(n*n)+idx]=hist[(n*n)+idx]+1; //incremento cuenta
    }

  //Histograma:
  printf("1)Test pick_site\n");
  printf("Histograma\n");
  printf("clase\tcuenta\n");
  
  for(int i=0; i<(n*n);i++)
    { 
      printf("%d\t%f\n",hist[i],(float)hist[(n*n)+i]/iter);
    }
  printf("\n");

  //2)Test flip: con una red de 3x3
  printf("2)Test flip\n");
  //Caso: DeltaE=+8
  int numflips=0;
  float pi;
  srand(time(NULL));
  for (int i=0;i<iter;i++)
    {
    
       lattice[0]=-1;
       lattice[1]=1;
       lattice[2]=-1;
       lattice[3]=1;
       lattice[4]=1;
       lattice[5]=1;
       lattice[6]=-1;
       lattice[7]=1;
       lattice[8]=-1;
       idx=4;
  
       pi=flip(lattice, n, T, idx, H, J, &E, &M);//hago q flip devuelva pi para comparar
       while(swich<1){
	   printf("pi %f\t",pi);
	   swich=1;}
       
       //Cuento los flips
       if (lattice[4]<0)
        {
	  numflips=numflips+1;
        }
       else{}
    }
  
  printf("probadeacept=%f\n\n",(float)numflips/iter);

  //3)Test para Energia
       printf("3)Test Energia\n");
       //Red conocida:
       lattice[0]=-1;
       lattice[1]=-1;
       lattice[2]=-1;
       lattice[3]=-1;
       lattice[4]=-1;
       lattice[5]=-1;
       lattice[6]=-1;
       lattice[7]=-1;
       lattice[8]=-1;

       E=energia(lattice, n, H, J);
       printf("Energia %f\n\n",E);

  //4)Test para Magnetizacion

        printf("4)Test Magnetizacion\n");
        M=magnetizacion(lattice,n);
	printf("Magnetizacion %d\n\n",M);
	//printf("\n");

  //5)Test para CPC:
       printf("4)Test CPC\n");
       int *spinborde=malloc(4*sizeof(int));

       //Red conocida:
       lattice[0]=1;
       lattice[1]=0;
       lattice[2]=0;
       lattice[3]=-1;
       lattice[4]=1;
       lattice[5]=0;
       lattice[6]=-1;
       lattice[7]=-1;
       lattice[8]=1;
       //Iprimo red
       imprimir(lattice,n);
       //Voy recorriendo el borde e imprimiendo los sij con sus 4 vecinos imediatos sl sr su sd.

       //Borde superior
          printf("Borde superior\n");
          int i=0;
          for (int j=0;j<n;j++)
	    {
             CPC(lattice, n, i, j, spinborde); //devuelve en spinborde sl sr su y sd.
             printf("s_%d%d:%d sl:%d sr:%d su:%d sd:%d\n",i,j,lattice[i*n+j],spinborde[0],spinborde[1],spinborde[2],spinborde[3]);
            }
          printf("\n");
       //Borde derecho
          printf("Borde derecho\n");
          int j=n-1;
          for (i=0;i<n;i++)
	   {
            CPC(lattice, n, i, j, spinborde); //devuelve en spinborde sl sr su y sd.
            printf("s_%d%d:%d sl:%d sr:%d su:%d sd:%d\n",i,j,lattice[i*n+j],spinborde[0],spinborde[1],spinborde[2],spinborde[3]);
           }
          printf("\n");
       //Borde inferior
          printf("Borde inferior\n");
          i=n-1;
          for (j=0;j<n;j++)
	   {
            CPC(lattice, n, i, j, spinborde); //devuelve en spinborde sl sr su y sd.
            printf("s_%d%d:%d sl:%d sr:%d su:%d sd:%d\n",i,j,lattice[i*n+j],spinborde[0],spinborde[1],spinborde[2],spinborde[3]);
           }
          printf("\n");
       //Borde izquierdo
	   printf("Borde izquierdo\n");
           j=0;
           for (i=0;i<n;i++)
	    {
             CPC(lattice, n, i, j, spinborde); //devuelve en spinborde sl sr su y sd.
             printf("s_%d%d:%d sl:%d sr:%d su:%d sd:%d\n",i,j,lattice[i*n+j],spinborde[0],spinborde[1],spinborde[2],spinborde[3]);
            }
	    printf("\n");
  return 0;
}
