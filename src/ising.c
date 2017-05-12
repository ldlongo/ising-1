#include <stdlib.h>
#include <time.h>
#include "metropolis.h"
#include "lattice.h"
#include <unistd.h>

int main(int argc, char **argv) {
  int n = 16;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.1;
  float T = 2.0;
  int niter = 2000;
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  // for (int i = 0; i < niter; i++) {
  // metropolis(lattice, n, T);
  // }
  pick_site(lattice, n);
  print_lattice(lattice, n);
  return 0;
}