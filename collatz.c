#include "lib/collatzUtils.h"
#include "lib/sharedMemory.h"
#include <fcntl.h>
#include <signal.h>
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

  uint64_t *shared_results = attachSharedStepsForNumber();
  atomic_uint_fast64_t *shared_top_number = attachNextToCompute();

  // this is weird
  atomic_uint *workers_active_counter = attachActiveWorkersCounter();
  atomic_fetch_add(workers_active_counter, 1);

  while (0 == 0) {
    uint64_t current_number = atomic_fetch_add(shared_top_number, 1);

    if (current_number >= max_steps) {

      // Results are saved without this calls
      /* syncSharedResults(shared_results); */
      /* syncTopNumber(shared_top_number); */

      // its probably not a good approach
      // signal handling?
      /* printf(""); */
      /* atomic_fetch_sub(workers_active_counter, 1); */
      /* while (atomic_fetch_add(workers_active_counter, 0) > 0) { */
      /* } */

      return 0;
    }

    min_numbers_for_step(current_number,
                         shared_results + indexOfNumber(current_number));
  }
}
