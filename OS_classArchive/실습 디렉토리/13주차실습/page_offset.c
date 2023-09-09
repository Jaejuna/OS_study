#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096   // 페이지 크기 정의 4KB

int main(int argc, char *argv[]) {

    // 인자(주소) 체크
    if (argc != 2) {
        fprintf(stderr, "Usage: ./address_translation <virtual address>\n");
        return -1;
    }

    // CLI 인자 숫자로 변환
    unsigned int address = atoi(argv[1]);

    // 페이지 사이즈의 offset과 페이지 수 계산
    // 페이지 수 계산
    unsigned int page_number = address / PAGE_SIZE;

    // offset 계산
    unsigned int offset = address % PAGE_SIZE;

    printf("The address %d contains:\n", address);
    printf("page number = %d\n", page_number);
    printf("offset = %d\n", offset);

    return 0;
}
