//This program can be used to time the execution of the parrarel collatz programs
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <no_of_processes> <max_steps>\n", argv[0]);
    return 1;
  }

  int no_of_processes = atoi(argv[1]);
  char *max_step = argv[2];

  if (!fork()) {
    execlp("rm", "rm", "-f", "/dev/shm/collatz_sh_mem", "/dev/shm/sem.init_sem", "/dev/shm/sem_init_flag", "/dev/shm/top_number_sh_mem", NULL);
  }
  wait(NULL);

  for (int i = 0; i < no_of_processes; ++i) {
    if (!fork()) {
      execl("./collatz", "./collatz", max_step, NULL);
    }
  }

  wait(NULL);
  return 0;
}
