#include "sharedMemory.h"
#include <error.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SH_SEM_INITIALIZED_FLAG "/sem_init_flag"

struct Results *attachSharedResults(int noOfElements) {
  int shMemFd = shm_open(SH_MEM_NAME, O_RDWR | O_CREAT, 0600);
  ftruncate(shMemFd, sizeof(struct Results));

  struct Results *results =
      mmap(NULL, sizeof(struct Results), PROT_READ | PROT_WRITE, MAP_SHARED,
           shMemFd, 0);

  int initializedFd = shm_open(SH_SEM_INITIALIZED_FLAG, O_RDWR | O_CREAT, 0600);
  ftruncate(initializedFd, sizeof(bool));
  bool *initialized = mmap(NULL, sizeof(bool), PROT_READ | PROT_WRITE,
                           MAP_SHARED, initializedFd, 0);

  printf("Initialized: %d\n", *initialized);
  if (*initialized == false) {
    for (int i = 0; i < noOfElements; i++) {
      sem_init(&results->minSteps[i].semaphore, 1, 1);
    }
  }

  close(shMemFd);
  close(initializedFd);
  return results;
}

atomic_uint_fast64_t *attachNextToCompute() {
  int shNextNumberFd = shm_open(SH_TOP_COUNTER_NAME, O_RDWR | O_CREAT, 0600);
  ftruncate(shNextNumberFd, sizeof(uint64_t));

  atomic_uint_fast64_t *shared_top_number =
      mmap(NULL, sizeof(atomic_uint_fast64_t), PROT_READ | PROT_WRITE,
           MAP_SHARED, shNextNumberFd, 0);

  if (*shared_top_number == 0) {
    *shared_top_number = 11;
  }

  close(shNextNumberFd);

  return shared_top_number;
}

atomic_uint *attachActiveWorkersCounter() {
  int fd = shm_open(SH_WORKERS_ACTIVE_COUNTER_NAME, O_RDWR | O_CREAT, 0600);
  ftruncate(fd, sizeof(atomic_uint));
  atomic_uint *counter = mmap(NULL, sizeof(atomic_uint), PROT_READ | PROT_WRITE,
                              MAP_SHARED, fd, 0);
  close(fd);
  return counter;
}

void printResults(struct Results *shared_results, uint64_t max_steps) {
  if (max_steps < 11) {
    perror("Cannot print results for less than 11 steps.");
    return;
  }

  for (uint64_t i = 11; i < max_steps; ++i) {
    printf("%ld: ", i);
    for (uint64_t j = 0; j < 5; ++j) {
      printf("%ld ", shared_results->minSteps[i].index[j]);
    }
    printf("\n");
  }
}

void populateResults(struct Results *shared_results, uint64_t collatzArgument,
                     uint64_t noOfSteps) {

  sem_wait(&shared_results->minSteps[noOfSteps].semaphore);

  bool filledInFlag = false;
  int maxNumberId = 0;

  for (uint64_t i = 0; i < 5; ++i) {
    if (shared_results->minSteps[noOfSteps].index[i] == 0) {

      /* printf("Inserting %ld at %ld\n", collatzArgument, noOfSteps); */

      shared_results->minSteps[noOfSteps].index[i] = collatzArgument;

      int temp = atomic_fetch_add(&shared_results->fillInCounter, 1);
      
      filledInFlag = true;

      break;
    }

    // Needed for the case when bigger wrong number got already filled in
    // and the array is full
    if (shared_results->minSteps[noOfSteps].index[i] >
        shared_results->minSteps[noOfSteps].index[maxNumberId]) {
      maxNumberId = i;
    }
  }

  if (!filledInFlag) {
    if (shared_results->minSteps[noOfSteps].index[maxNumberId] > collatzArgument) {
      shared_results->minSteps[noOfSteps].index[maxNumberId] = collatzArgument;
    }
  }

  sem_post(&shared_results->minSteps[noOfSteps].semaphore);
}
