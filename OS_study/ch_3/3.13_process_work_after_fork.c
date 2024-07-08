//fork 이후의 프로세스 실행 예제
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    
    if(pid>0) //부모 프로세스라면 wait 조건문 (자식 프로세스 대기)
    {
        wait(NULL);
    }
    printf("Hello, Process! %d\n", pid);
    return 0;
}