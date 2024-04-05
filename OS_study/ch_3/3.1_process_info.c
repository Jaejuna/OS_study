// 프로세스 정보를 출력하는 코드
// size ./3.1_process_info 로 결과값 반환

#include <stdio.h>
#include <stdlib.h>

int x;
int y = 15;

int main(int argc, char *argv[])
{
    int *values;
    int i;

    values = (int *) malloc(sizeof(int)*5);

    for(i=0; i<5; i++)
    {
        values[i] = i;
    }
    return 0;
}