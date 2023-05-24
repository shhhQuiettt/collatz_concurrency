#include "collatzUtils/collatzUtils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <max_steps>\n", argv[0]);
    return 1;
  }

  const uint32_t MAX_STEPS = atoi(argv[1]);

  for (uint32_t s = 11; s < MAX_STEPS; s++) {
    natural_number result[5];
    min_numbers_for_step(s, &result);
  }
}
