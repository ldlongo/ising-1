#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "metropolis.h"

int  imprimir(int *lattice, int n){
    int j;
    int i;
    int s;
    j=1;
    s=n*n;
    for (i=0;i<s;i=i+1){

        if (j!=n)
         {printf("%2d\t",lattice[i]);
         j=j+1;}
        else
         {j=1;
         printf("%2d\n",lattice[i]);}
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

         E=E+J*sij*(su+sd+sl+sr);
      }
      }
  //Imprimo la energia
  E=E/2;//se divide por dos porque en la suma cuento dos veces sobre el mismo par
  printf("Eant=%3d ",E); //imprimo energia vieja */
  

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

   //Calculo Beta*DeltaT
   float pi=lut[5+(DeltaE+8)/4];
   printf("DeltaE:%2d ", DeltaE);
   printf("pi=%f ",pi);

   //Acepto o Rechazo
    if (pi>1)
     {
       lattice[idx]=lattice[idx]*(-1); //acepto con probabilidad 1 significa hacer el flip  
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
	     lattice[idx]=lattice[idx]*(-1) ;  //hago el flip
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
