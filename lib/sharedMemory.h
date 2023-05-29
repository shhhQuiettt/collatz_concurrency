#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H
#endif

#include <stdatomic.h>
#include <stdint.h>

volatile uint64_t *attachSharedResults();

volatile atomic_uint_fast64_t *attachTopNumber();

atomic_uint *attachActiveWorkersCounter();

void syncTopNumber(volatile atomic_uint_fast64_t *shared_top_number);

void syncSharedResults(volatile uint64_t *shared_results);

int indexOfNumber(uint64_t number);

void printResults(volatile uint64_t *shared_results, uint64_t max_steps);
