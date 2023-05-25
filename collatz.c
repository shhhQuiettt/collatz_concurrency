#include "lib/collatzUtils.h"
#include "lib/sharedMemory.h"
#include <fcntl.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <max_steps>\n", argv[0]);
    return 1;
  }


  const uint64_t max_steps = atoi(argv[1]);

  volatile uint64_t *shared_results = attachSharedResults();
  volatile atomic_uint_fast64_t *shared_top_number = attachTopNumber();

  while (0 == 0) {
    uint64_t current_number = atomic_fetch_add(shared_top_number, 1);

    /* printf("I am process %d, and I am working on %ld\n", getpid(), */
           /* current_number); */

    if (current_number >= max_steps) {
      return 0;
    }

    min_numbers_for_step(current_number,
                         shared_results + indexOfNumber(current_number));
  }
}
