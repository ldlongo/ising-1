#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "metropolis.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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


int metropolis(int *lattice, int n, float T) {
  //Elijo spin random
  int idx=pick_site(lattice, n);
  //Me fijo s hago o no el flip
  flip(lattice,n,T,idx);
 return 0;
}

int pick_site(int *lattice, int n) {
  int j;
  int idx; //idx es la posicion del vector lattice que voy a  flipear( 1< idx< n*n)
  idx =(int)((float)rand()*n*n/RAND_MAX);
  printf("Pick:%3d ",idx);
  return idx;
}

int flip(int *lattice, int n, float T, int idx) {
  extern float *lut; //variable externa puntero a tabla. Evita calcular las exponenciales cada vez que se llama a flip. 
  //Calculo la energia Eo=E(s)
   int E;
   int M;
   int J=-1;
   E=energia(lattice,n);
   M=magnetizacion(lattice,n);
   printf("Eant:%3d ",E); //imprimo energia vieja 
   printf("Mant:%3d ",M);//imprimo magnetizacion vieja 

   int i=idx/n;//Paso de idx a i, j
   int j=idx%n;
   
  
   int  jl=(j-1+n)%n;  //j_ izq
   int  jr=(j+1+n)%n;  //j_dcha
   int  iu=(i-1+n)%n;  //i_arriba
   int  id=(i+1+n)%n;  //i_abajo

   int  sij=lattice[i*n+j]; //el actual

   int  sr=lattice[i*n+jr];
   int  sl=lattice[i*n+jl];
   int  su=lattice[iu*n+j];
   int  sd=lattice[id*n+j];

   //Calculo la variacion de energia si lo diera vuelta:
   int DeltaE=-2*J*sij*(su+sd+sr+sl);
   int DeltaM=2*sij;

   //Calculo Beta*DeltaT
   float pi=lut[5+(DeltaE+8)/4];
   printf("DeltaE:%2d ", DeltaE);
   printf("DeltaM:%2d ",DeltaM);
   printf("pi:%f ",pi);

   //Acepto o Rechazo
    if (pi>1)
     {
       lattice[idx]=lattice[idx]*(-1); //acepto con probabilidad 1 significa hacer el flip  
       printf("acepto  ");
       E=E+DeltaE;              //actualizo energia
       M=M+DeltaM;              //actualizo magnetizacion
       printf("Enva:%3d ",E);   //imprimo la energia nueva
       printf("Mnva:%3d\n",M); //imprimo la magnet nueva
     }
   else
     {
       //acepto con probabilidad pi
       float moneda=(float)rand()/(float)RAND_MAX;
       printf("moneda=%f ",moneda);
	 if (moneda<pi)
	   {
	     printf("acepto  ");
	     lattice[idx]=lattice[idx]*(-1) ;  //hago el flip
 	     E=E+DeltaE;              //actualizo energia
	     M=M+DeltaM;              //actualizo magnet
	     printf("Enva:%3d ",E);  //imprimo la energia nueva
	     printf("Mnva:%3d\n",M); //imprimo la  magnet nueva
	     
	   }
	 else
	   {
             printf("rechazo ");      //no hago el flip
	     printf("Enva:%3d ",E); //imprimo la energia que no habra cambiado
	     printf("Mnva:%3d\n",M); //imprimo la magnetizacion que no habra cambiado
	   }
     }
  return 0;
}

int energia(int *lattice, int n){
  int E=0;
  int J=-1;
  //Todo esto lo mando a una funcion energia(lattice,n)
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

         E=E+J*sij*(su+sd+sl+sr);
      }
     }
 //Imprimo la energia
 E=E/2;//se divide por dos porque en la suma cuento dos veces sobre el mismo par
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
