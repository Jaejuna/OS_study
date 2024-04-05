//fork 이후의 프로세스 실행 예제
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    
    if(pid>0)
    {
        wait(NULL);
    }
    printf("Hello, Process! %d\n", pid);
    return 0;
}