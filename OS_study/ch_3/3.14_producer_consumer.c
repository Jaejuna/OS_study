// 생산자 소비자 문제

#include <stdbool.h> // bool 타입 사용을 위해 추가
#include <stdio.h> // printf 함수 사용을 위해 추가

#define BUFFER_SIZE 10 // 버퍼의 크기를 정의

// 버퍼에 저장될 아이템의 구조체 정의
typedef struct{
    // 아이템의 구조는 예시로 정수 값을 사용합니다.
    int value;
} item;

// 전역 버퍼와 인덱스 변수 선언
item buffer[BUFFER_SIZE];
int in = 0; // 생산자가 데이터를 삽입할 버퍼의 인덱스
int out = 0; // 소비자가 데이터를 추출할 버퍼의 인덱스

void producer(int value) {
    item next_produced; // 다음에 생산할 아이템

    while(true) {
        /* 아이템 생산 */
        next_produced.value = value; /* 값 설정 */

        // 버퍼가 가득 찼는지 확인
        while(((in + 1) % BUFFER_SIZE) == out) {
            // 버퍼가 가득 차면, 생산을 일시 중지 (무한 루프)
        }

        // 버퍼가 가득 차지 않았다면 아이템을 버퍼에 삽입
        buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE; // 인덱스 업데이트
    }
}

void consumer(void) {
    item next_consumed; // 다음에 소비할 아이템

    while(true) {
        // 버퍼가 비어 있는지 확인
        while(in == out) {
            // 버퍼가 비어 있으면, 소비를 일시 중지 (무한 루프)
        }

        // 버퍼가 비어 있지 않다면 아이템을 추출
        next_consumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE; // 인덱스 업데이트
        
        /* 아이템 소비 */
        printf("Consumed: %d\n", next_consumed.value);
    }
}

int main() {
    // 더미 데이터로 테스트
    for(int i = 0; i < 15; i++) {
        producer(i);
    }
    
    for(int j = 0; j < 15; j++) {
        consumer();
    }

    return 0;
}