#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H
#endif

#include <semaphore.h>
#include <stdatomic.h>
#include <stdint.h>


#define MAX_MAX_STEPS 10000000

#define SH_MEM_NAME "/collatz_sh_mem"
#define SH_TOP_COUNTER_NAME "/top_number_sh_mem"
#define SH_SEM_INITIALIZED_FLAG "/sem_init_flag"

#define SEM_TOP_NUMBER_NAME "/sem_top_number"
#define SEM_INIT_RESULTS_NAME "/sem_init_result8"

struct MinNumberForStep {
  uint64_t index[5];
  sem_t semaphore;
};

struct Results {
  atomic_uint fillInCounter;
  struct MinNumberForStep minSteps[MAX_MAX_STEPS];
};

struct Results *attachSharedResults(int noOfElements);

atomic_uint_fast64_t *attachNextToCompute();

atomic_uint *attachActiveWorkersCounter();

int indexOfNumber(uint64_t number);

void printResults(struct Results *shared_results, uint64_t max_steps);

void populateResults(struct Results *shared_results, uint64_t current_number,
                     uint64_t noOfSteps);
