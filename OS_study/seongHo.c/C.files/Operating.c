#include <stdio.h>
#include <unistd.h>
#include <math.h>
int main()
{
    pid_t pid;
    pid = fork();
    printf("Hello, Process! %d\n", pid);
}
/*process id 출력, 그리고 child process에서 PID, which is 0*/

// 2547, 0