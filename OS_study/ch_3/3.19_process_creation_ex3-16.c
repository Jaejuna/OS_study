#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 5 

int nums[SIZE] = {0, 1, 2, 3, 4};

int main() {
  pid_t pid; 
  int i; 
  pid = fork();

  if (pid == 0) { // child process
    for (i = 0; i < SIZE; i++) {
      nums[i] *= i; 
      printf("CHILD: %d \n", nums[i]); // LINE X
    }
  }
  else if (pid > 0) { // parent process
    wait(NULL);
    for (i = 0; i < SIZE; i++) {
      printf("PARENT: %d \n", nums[i]); // LINE X
    }
  }
  return 0;
}
