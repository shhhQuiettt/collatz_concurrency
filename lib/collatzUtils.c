#include <stdint.h>
#include <semaphore.h>
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
