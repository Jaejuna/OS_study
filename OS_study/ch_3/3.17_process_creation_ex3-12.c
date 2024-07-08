// will 'LINE J' printed?

#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid; 
  pid = fork();
  
  if (pid == 0) { // child process
    execlp("/bin/ls", "ls", NULL); // PCB에 정보가 바뀐다? 그래서 LINE J는 출력되지 않는다.
    printf("LINE J\n");
  } else if (pid > 0) { // parent process
    wait(NULL); 
    printf("Child Complete\n");
  }
  
  return 0;
}
