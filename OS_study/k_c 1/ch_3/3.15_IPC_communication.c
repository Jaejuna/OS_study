// IPC 통신 예제

#include <stdio.h>
#include <stdbool.h>

// 메시지 구조체 정의
typedef struct {
    int data; // 메시지에 포함될 데이터
} message;

// 메시지를 전송하는 더미 함수
void send(message msg) {
    printf("Produced: %d\n", msg.data);
}

// 메시지를 수신하는 더미 함수
void receive(message *msg) {
    // 실제 구현에서는 메시지 큐나 버퍼에서 메시지를 가져오지만,
    // 여기서는 예시로 메시지 내용을 직접 설정합니다.
    msg->data = msg->data + 1; // 데이터를 1 증가시킴 (가정)
    printf("Consumed: %d\n", msg->data);
}

int main() {
    // 더미 데이터로 테스트
    message msg;
    msg.data = 0; // 초기 데이터 설정

    // 간단한 테스트를 위한 루프
    for(int i = 0; i < 5; i++) {
        msg.data = i; // 데이터 생성
        send(msg); // 데이터 전송 (생산자)
        receive(&msg); // 데이터 수신 및 처리 (소비자)
    }

    return 0;
}
