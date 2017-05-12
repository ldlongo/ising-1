
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lattice.h"
#include "metropolis.h"

///int metropolis(int *lattice, int n, float T) {
// return 0;
//}

int pick_site(int *lattice, int n) {
  int j;
  int idx; //idx es la posicion del vector lattice que voy a  flipear( 1< idx< n*n)
  idx =(float)rand()*n*n/(float)RAND_MAX;
  printf("%d\n",idx);
  return  ;
}

int flip(int *lattice, int n, float T, float idx) {
  *lattice[idx]=*lattice[idx]*(-1);
return 0;
}
