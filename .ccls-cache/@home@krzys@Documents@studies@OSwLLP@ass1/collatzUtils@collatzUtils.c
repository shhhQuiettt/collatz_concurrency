#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t natural_number;

uint64_t no_of_colnatz_steps(natural_number x) {
  uint64_t steps = 0;
  while (x != 1) {   // until you reach 1,
    if (x % 2)       // if the number is odd,
      x = 3 * x + 1; // multiply it by three and add one,
    else             // else, if the number is even,
      x /= 2;        // divide it by two
    ++steps;
  }
  return steps;
}

void min_numbers_for_step(uint32_t s, natural_number (*result)[5]) {
  uint8_t min_counter = 0;
  const int threshold = 1000000;
  natural_number candidate = 1;

  while (min_counter < 5) {
    if (threshold < candidate) {
      printf("No solution found for %d\n, with threshold: %d", s, threshold);
      break;
    }

    if (no_of_colnatz_steps(candidate) == s) {
      (*result)[min_counter] = candidate;
      ++min_counter;
    }

    ++candidate;
  }
}
