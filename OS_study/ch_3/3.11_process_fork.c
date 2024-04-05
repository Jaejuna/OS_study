// 프로세스 포크 예제 코드
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    printf("Hello, Process!\n");
    return 0;
}