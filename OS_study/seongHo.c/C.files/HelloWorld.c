#include <stdio.h>
#include <unistd.h>
#include <math.h>
int main()
{
    pid_t pid;
    pid = fork();
    printf("Hello, Process!/n");
}
/*Hello, process needs to be printed twice*/




