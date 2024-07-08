// LINE A의 값 구하기 연습 문제

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 5;

int main() {
  pid_t pid; 
  pid = fork();
  
  if (pid == 0) { // child process
    value += 15;
    printf("Child: value = %d\n", value); // child process value
    return 0;
  } else if (pid > 0) { // parent process
    wait(NULL); 
    printf("Parent: value = %d\n", value); // LINE A
  }
}
