#ifndef COLLATZ_UTILS_H
#define COLLATZ_UTILS_H
#endif

#include <stdint.h>
#include <stdio.h>

typedef uint64_t natural_number;

uint64_t no_of_colnatz_steps(natural_number x);

void min_numbers_for_step(uint32_t s, natural_number (*result)[5]);
