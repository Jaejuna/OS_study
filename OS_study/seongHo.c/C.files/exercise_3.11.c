#include <stdio.h>
#include <unistd.h>


int main()
{
    int i;
    pid_t pid
    for (i=0; i < 4; i++) {
        pid = fork();
        printf("Hello, Fork\n", pid);
    }
    return 0;
}

// 16개의 새끼를 만든다, child