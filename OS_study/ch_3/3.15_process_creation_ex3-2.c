/*
* How many processes are created? = 8
*/

#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h>

int main() {

fork(); // fork a child process 
fork(); // fork another child process 
fork(); // and fork another

return 0;
}