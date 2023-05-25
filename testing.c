#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef uint64_t natural_number;

#define SH_MEM_NAME "collatz_sh_mem"
#define MAX_MAX_STEPS 10000000
#define SH_MEM_SIZE (MAX_MAX_STEPS * 5 * sizeof(natural_number))

int main() {

  int sh_mem_fd = open(SH_MEM_NAME, O_RDWR | O_CREAT, 0600);
  ftruncate(sh_mem_fd, SH_MEM_SIZE);

  uint64_t *shared_results =
      mmap(NULL, SH_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, sh_mem_fd, 0);

  printf("shared_results: %d, %d, %d, %d, %d", shared_results[11*5], shared_results[11*5+1], shared_results[11*5+2], shared_results[11*5+3], shared_results[11*5+4]);
}
