// 프로세스 포크 w/ pid 예제 코드
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    // 자식 프로세스의 pid가 출력되고, 자식 프로세스에서 fork() 호출하고 pid를 출력하면 0이 출력된다.
    printf("Hello, Process! %d\n", pid);
    
    return 0;
}