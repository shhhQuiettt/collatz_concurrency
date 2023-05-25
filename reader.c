#include "lib/sharedMemory.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <max_steps>\n", argv[0]);
    return 1;
  }

  int no_of_steps = atoi(argv[1]);

  volatile uint64_t *shared_results = attachSharedResults();
  printResults(shared_results, no_of_steps);
}
