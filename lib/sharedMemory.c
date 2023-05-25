#include <error.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_MAX_STEPS 10000000
#define SH_MEM_SIZE (MAX_MAX_STEPS * 5 * sizeof(uint64_t))

#define SH_MEM_NAME "./.data/collatz_sh_mem"
#define SH_TOP_COUNTER_NAME "./.data/top_number_sh_mem"

volatile uint64_t *attachSharedResults() {
  int sh_mem_fd = open(SH_MEM_NAME, O_RDWR | O_CREAT, 0600);
  ftruncate(sh_mem_fd, SH_MEM_SIZE);
  // should it be atomic?
  volatile uint64_t *shared_results =
      mmap(NULL, SH_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, sh_mem_fd, 0);

  return shared_results;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

volatile atomic_uint_fast64_t *attachTopNumber() {
  int sh_top_number_fd = open(SH_TOP_COUNTER_NAME, O_RDWR | O_CREAT, 0600);
  ftruncate(sh_top_number_fd, sizeof(uint64_t));
  volatile atomic_uint_fast64_t *shared_top_number =
      mmap(NULL, sizeof(atomic_uint_fast64_t), PROT_READ | PROT_WRITE,
           MAP_SHARED, sh_top_number_fd, 0);

  // is mutex neccessary?
  if (*shared_top_number == 0) {
    pthread_mutex_lock(&mutex);
    if (*shared_top_number == 0) {
      *shared_top_number = 11;
    }
    pthread_mutex_unlock(&mutex);
  }

  return shared_top_number;
}

int indexOfNumber(uint64_t number) { return 5 * number; }

void printResults(volatile uint64_t *shared_results, uint64_t max_steps) {
  if (max_steps < 11) {
    perror("Cannot print results for less than 11 steps.");
    return;
  }
  for (uint64_t i = 11; i < max_steps; ++i) {
    printf("%ld: ", i);
    for (uint64_t j = 0; j < 5; ++j) {
      printf("%ld ", *(shared_results + indexOfNumber(i) + j));
    }
    printf("\n");
  }
}

void syncTopNumber(volatile atomic_uint_fast64_t *shared_top_number) {
  msync((void *)shared_top_number, sizeof(atomic_uint_fast64_t), MS_SYNC);
}

void syncSharedResults(volatile uint64_t *shared_results) {
  msync((void *)shared_results, SH_MEM_SIZE, MS_SYNC);
}
