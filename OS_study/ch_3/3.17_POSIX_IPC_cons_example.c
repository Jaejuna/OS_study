// POSIX Shared Memory API를 보여주는 소비자 프로세스
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
    const int SIZE = 4096;                      // 공유 메모리의 크기
    const char* name = "OS";                    // 공유 메모리의 이름
    
    int shm_fd;                                 // 공유 메모리의 파일 디스크립터
    char* ptr;                                  // 공유 메모리의 포인터

    // 공유 메모리 객체 생성
    shm_fd = shm_open(name, O_RDONLY, 0666);
    
    // 공유 메모리 객체를 현재 프로세스의 주소 공간에 매핑
    ptr = (char*) mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // 공유 메모리에서 메시지 읽기
    printf("%s", (char*)ptr);

    // 공유 메모리 객체 제거
    shm_unlink(name);

    return 0;
}
