#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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
  E=E/2;//se divide por dos porque en la suma cuento dos veces sobre el mismo par
  printf("Eant=%3d ",E); //imprimo energia vieja
  
  //Elijo spin random
  int idx=pick_site(lattice, n);
  
  //Calculo la energia nueva E(-s) o mejor DeltaE
  //Saco i y j del idx
   int i=idx/n;
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

   int DeltaE=-2*J*sij*(su+sd+sr+sl);
  
  //Calculo Beta*DeltaT
   float B=(float) 1/(float)T;
   double e=exp(1.);
   float pi=pow(e,-B*DeltaE);
   printf("DeltaE:%2d ", DeltaE);
   printf("pi=%f ",pi);

  //Acepto o Rechazo
   if (pi>1)
     {
       flip(lattice,n,T,idx);  //acepto con probabilidad 1 significa hacer el flip
       printf("acepto  ");
       E=E+DeltaE;             //actualizo energia
       printf("Enva=%3d\n",E); //imprimo la energia nueva
     }
   else
     {
       //acepto con probabilidad pi
       float moneda=(float)rand()/(float)RAND_MAX;
       printf("moneda=%f ",moneda);
	 if (moneda<pi)
	   {
	     printf("acepto  ");
	     flip(lattice,n,T,idx);  //hago el flip
 	     E=E+DeltaE;             //actualizo energia
	     printf("Enva=%3d\n",E); //imprimo la energia nueva
	   }
	 else
	   {
             printf("rechazo ");      //no hago el flip
	     printf("Enva=%3d\n",E); //imprimo la energia que no habra cambiado
	   }
     }
  
 return 0;
}

int pick_site(int *lattice, int n) {
  int j;
  int idx; //idx es la posicion del vector lattice que voy a  flipear( 1< idx< n*n)
  idx =(int)((float)rand()*n*n/(float)RAND_MAX);
  printf("Cambio:%d ",idx);
  return idx;
}

int flip(int *lattice, int n, float T, int idx) {
  lattice[idx]=lattice[idx]*(-1);
  return 0;
}
