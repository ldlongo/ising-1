#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "funciones.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int pick_site(int *lattice, int n) {
  int j;
  int idx; //idx es la posicion del vector lattice que voy a  flipear( 1< idx< n*n)
  idx =(int)((float)rand()*n*n/RAND_MAX);
  // printf("Pick:%3d ",idx);
  return idx;
}

float flip(int *lattice, int n, float T, int idx, float H, float J, float *pE, int *pM) {
   extern float *lut; //variable externa puntero a tabla. Evita calcular las exponenciales cada vez que se llama a flip.
   extern float *lut2;

   //Condiciones periodicas de contorno:
   
    int i=idx/n;//Paso de idx a i, j
    int j=idx%n;
    int *spinborde=malloc(4*sizeof(int));
    CPC(lattice, n, i, j, spinborde);
    int  sij=lattice[i*n+j]; //el actual

   //Calculo la variacion de energia y magnetizacion  si lo diera vuelta:
    
    int DeltaE=2*J*sij*(spinborde[0]+spinborde[1]+spinborde[2]+spinborde[3]);
    int DeltaM=-2*sij; //el negativo es porque si hay un +1 el cambio es del signo opuesto.

   //Calculo Beta*DeltaT y pi:
    
    int idxtabla2=(sij+1+4)/2; // si sij=-1 corresponde con la pos 2 y si sij=1 con la pos 3 de la tabla 2 
    float pi=lut[5+(DeltaE+8)/4]*lut2[idxtabla2];
    
   //Acepto o Rechazo:
    
    if (pi>1)
     {
       lattice[idx]=lattice[idx]*(-1); //acepto con probabilidad 1 significa hacer el flip  
       *pE=*pE+DeltaE;
       *pM=*pM+DeltaM;
     }
   else
     {
       //acepto con probabilidad pi
       float moneda=(float)rand()/(float)RAND_MAX;
	 if (moneda<pi)
	   {
	     lattice[idx]=lattice[idx]*(-1) ;  //hago el flip
 	    *pE=*pE+DeltaE;
            *pM=*pM+DeltaM;      
	   }
	 else{}
     }
  free(spinborde);  
  return pi;
}

int imprimir(int *lattice, int n){
    int j;
    int i;
    int s;
    j=1;
    s=n*n;
    for (i=0;i<s;i=i+1){

        if (j!=n)
         {
     if (lattice[i]<0)
       {
         printf(ANSI_COLOR_RED "%2d\t" ANSI_COLOR_RESET,lattice[i]);
       }
     else
       {
         printf(ANSI_COLOR_GREEN "%2d\t" ANSI_COLOR_RESET,lattice[i]);
       }
           j=j+1;
   }
        else
         { j=1;
     if (lattice[i]<0)
       {  
               printf(ANSI_COLOR_RED "%2d\n" ANSI_COLOR_RESET,lattice[i]);
       }
     else
       {
         printf(ANSI_COLOR_GREEN "%2d\n" ANSI_COLOR_RESET,lattice[i]);
       }
   }
    }
    printf("\n");  
    return 0;
}

int CPC(int *lattice, int n, int i, int j, int* spinborde){
  
   int  jl=(j-1+n)%n;  //j_ izq
   int  jr=(j+1+n)%n;  //j_dcha
   int  iu=(i-1+n)%n;  //i_arriba
   int  id=(i+1+n)%n;  //i_abajo

   int  sij=lattice[i*n+j]; //el actual

   int  sr=lattice[i*n+jr];
   int  sl=lattice[i*n+jl];
   int  su=lattice[iu*n+j];
   int  sd=lattice[id*n+j];

   spinborde[0]=lattice[i*n+jl]; //sl
   spinborde[1]=lattice[i*n+jr]; //sr
   spinborde[2]=lattice[iu*n+j];//su
   spinborde[3]=lattice[id*n+j]; //sd
       
   return 0;
}

int energia(int *lattice, int n, float H, float J){
  int E=0;
  int *spinborde=malloc(4*sizeof(int));
  //Todo esto lo mando a una funcion energia(lattice,n)
  for (int i=0;i<n;i++)
    {
    for (int j=0;j<n;j++)
      {
        
        //Condiciones periodicas de contorno:

	   CPC(lattice, n, i, j, spinborde);
    
           int  sij=lattice[i*n+j]; //el actual 
	   //Energia acumulo: pongo el dos en  H*2*sij  para no afectar al termino que tiene el campo magnetico luego cuando hago E=E/2.
           E=E-J*sij*(spinborde[0]+spinborde[1]+spinborde[2]+spinborde[3])-H*2*sij; 
      }
     }
 //Imprimo la energia
 E=E/2;//se divide por dos porque en la suma cuento dos veces sobre el mismo par
 free(spinborde);
 return E;
}

int magnetizacion(int *lattice,int n){
  int M=0;
  int sij;
  for (int i=0;i<n;i++)
    {
      for (int j=0;j<n;j++)
      {
         sij=lattice[i*n+j]; //el actual 
	 M=M+sij;	 
      }
    } 
  return M;
}
