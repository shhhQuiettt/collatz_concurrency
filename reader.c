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
  volatile atomic_uint_fast64_t* top_number = attachTopNumber();
  if (*top_number < no_of_steps - 1) {
    fprintf(stderr, "No results enaugh result to print. (Top number: %ld), (Wanted: %d)\n", *top_number, no_of_steps);
    return 1;
  }
  volatile uint64_t *shared_results = attachSharedResults();

  printResults(shared_results, no_of_steps);
}
