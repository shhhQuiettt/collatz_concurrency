#include "lib/collatzUtils.h"
#include "lib/sharedMemory.h"
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define INIT_SEM_NAME "/init_sem"

struct Results *shared_results;
sem_t *init_sem;
bool endFlag = false;

void handleSigint(int sig) {
  if (sig == SIGINT) {
    endFlag = true;
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <max_steps>\n", argv[0]);
    return 1;
  }

  const uint64_t max_steps = atoi(argv[1]);
  init_sem = sem_open(INIT_SEM_NAME, O_CREAT, 0600, 1);

  sem_wait(init_sem);
  shared_results = attachSharedResults(max_steps);
  atomic_uint_fast64_t *sharedNextToCompute = attachNextToCompute();
  sem_post(init_sem);

  signal(SIGINT, handleSigint);

  const int nextToComputeOffset = 512;

  while (!endFlag &&
         atomic_load(&shared_results->filledInCounter) < 5 * (max_steps - 11)) {

    uint64_t current_number =
        atomic_fetch_add(sharedNextToCompute, nextToComputeOffset);

    for (int n = 0; n < nextToComputeOffset; ++n) {
      uint64_t computedNumber = current_number + n;

      uint64_t noOfSteps = no_of_colnatz_steps(computedNumber);

      if (noOfSteps >= 11 && noOfSteps < max_steps) {
        populateResults(shared_results, computedNumber, noOfSteps);
      }
    }
  }
}
