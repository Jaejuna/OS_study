#include <stdio.h>
#include <unistd.h>

int value = 5;
int main()
{
    fork(); // fork a child process
    value += 5;
    fork(); // fork another child process 
    value += 5;
    fork(); // and fork another
    value += 5;
    printf("Hello, fork()! %d\n", value);
    return 0;
}
//20만 출력됨