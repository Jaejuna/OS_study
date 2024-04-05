// message passing 방법 예제

// 생성자
message next_produced;

while(true){
	/* produce an item in next_produced */
    // next_produced안의 item에 정보를 생산하여 저장
    
    send(next_produced);	// 메시지 전송
}

//소비자
message next_consumed;

while(true){
	receive(next_consumed);
    
    /* consume the item in next_consumed*/
    // 소비자 프로세스는 이후 정보를 소비함
}