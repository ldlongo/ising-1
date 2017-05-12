#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  int n = 4;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.1;
  float T = 2.0;
  int niter = 2000;
  int idx;
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  // for (int i = 0; i < niter; i++) {
   metropolis(lattice, n, T);
  // } 
  print_lattice(lattice, n);
  return 0;
}
