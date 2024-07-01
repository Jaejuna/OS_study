#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int main()
{
    pid_t pid;
    pid = fork();
    if(pid>0) // parent process
        wait(NULL)
    printf("Hello, Process! %d\n", pid);
}
/*child process가 먼저 프린트 되는 상황*/

//0, 3004