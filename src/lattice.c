#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lattice.h"


int fill_lattice(int *lattice, int n, float p) {

  //Función que llena la red de nxn con probabilidad p.
    int i;
    float test;
    int s;
    s=n*n;
    for (i=0;i<s;i++){
      test = (float)rand()/(float)RAND_MAX;  
      /*Acepto o rechazo con probabilidad p*/
      if (test<p)
        {
	  lattice[i]=1;
        }
	else
        {
          lattice[i]=-1;
        }    
    }
  return 0;
}

int print_lattice(int *lattice, int n) {
    int j;
    int i;
    int s;
    j=1;
    s=n*n;
    for (i=0;i<s;i=i+1)
      {
        if (j!=n)
         {
          printf("%2d ",lattice[i]);
          j=j+1;
         }
        else
         {
          j=1;
          printf("%2d\n",lattice[i]);}
         }
      printf("\n");
 return 0;
 }
