#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid, pid1; 
  pid = fork(); 
  
  if (pid == 0) { // child process
    pid1 = getpid(); // 자신의 pid를 호출하는 시스템 콜
    printf("child: pid = %d\n", pid); // A 
    printf("child: pid1 = %d\n", pid1); // B
  } 
  else if (pid > 0) { // parent process
    // wait(NULL); // 차이점 알아보기
    pid1 = getpid(); 
    printf("parent: pid = %d\n", pid); // C 
    printf("parent: pid1 = %d\n", pid1); // D 
  } 
  
  return 0;
}
