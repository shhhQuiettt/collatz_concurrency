// This program reads the results of the collatz program
//
#include "lib/sharedMemory.h"

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <max_steps>\n", argv[0]);
    return 1;
  }

  int no_of_steps = atoi(argv[1]);
  struct Results *shared_results = attachSharedResults(no_of_steps);

  printResults(shared_results, no_of_steps);
}
