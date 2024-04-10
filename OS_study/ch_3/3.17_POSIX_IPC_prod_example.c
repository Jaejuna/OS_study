// POSIX Shared Memory API를 보여주는 생산자 프로세스
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // 파일 제어를 위한 헤더 파일
#include <unistd.h>
#include <sys/mman.h>   // 메모리 관리를 위한 헤더 파일

int main()
{
    const int SIZE = 4096;                      // 공유 메모리의 크기
    const char* name = "OS";                    // 공유 메모리의 이름
    const char* message_0 = "Hello, ";
    const char* message_1 = "Shared Memory!\n";
    
    int shm_fd;                                 // 공유 메모리의 파일 디스크립터
    char* ptr;                                  // 공유 메모리의 포인터

    // 공유 메모리 객체 생성
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    // 공유 메모리의 크기 설정
    ftruncate(shm_fd, SIZE);

    // 공유 메모리 객체를 현재 프로세스의 주소 공간에 매핑
    ptr = (char*) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // 공유 메모리에 메시지 작성
    sprintf(ptr, "%s", message_0);
    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);

    return 0;
}
