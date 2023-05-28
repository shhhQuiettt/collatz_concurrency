#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <no_of_processes> <max_steps>\n", argv[0]);
    return 1;
  }

  int no_of_processes = atoi(argv[1]);
  char *max_step = argv[2];


  if (!fork()){
      execlp("rm", "rm", "-r", "-f", "./.data", NULL);
  }
  wait(NULL);

  if (!fork()){
      execlp("mkdir", "mkdir", "./.data", NULL);
  }

  wait(NULL);

  for (int i = 0; i < no_of_processes; ++i) {
    if (!fork()) {
      execl("./collatz", "./collatz", max_step, NULL);
      return 0;
    }
  }

  wait(NULL);
  return 0;
}
