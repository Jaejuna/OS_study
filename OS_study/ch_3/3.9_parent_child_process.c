// 부모 프로세스와 자식 프로세스 예시
#include <stdio.h>  // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <unistd.h> // UNIX 표준 시스템 호출을 위한 헤더 파일
#include <sys/wait.h>   // wait() 함수를 사용하기 위한 헤더 파일

int main()
{
    pid_t pid; // pid_t는 프로세스 ID를 저장하는 데 사용되는 데이터 타입입니다.

    // fork() 함수를 호출하여 자식 프로세스를 생성합니다.
    // 부모 프로세스에서는 생성된 자식 프로세스의 PID를 반환받고,
    // 자식 프로세스에서는 0을 반환받습니다.
    pid = fork();
    
    if(pid < 0)   // fork() 호출 실패
    {
        // 표준 에러 스트림(stderr)에 에러 메시지를 출력합니다.
        fprintf(stderr, "Fork Failed");
        return 1; // 에러 발생 시, 프로그램을 비정상적으로 종료합니다.
    }
    else if(pid == 0) // 자식 프로세스인 경우
    {
        // execlp() 함수를 사용하여 "/bin/ls" 실행 파일을 실행합니다.
        // "ls"는 첫 번째 인자로 프로그램 이름을 나타냅니다.
        // NULL은 인자 리스트의 끝을 나타냅니다.
        execlp("/bin/ls", "ls", NULL);
    }
    else    // 부모 프로세스인 경우
    {
        // wait() 함수는 부모 프로세스가 자식 프로세스의 종료를 기다리게 합니다.
        // NULL 파라미터는 자식 프로세스의 종료 상태를 받지 않겠다는 것을 의미합니다.
        wait(NULL); 
        printf("Child Complete\n"); // 자식 프로세스가 종료되면 메시지를 출력합니다.
    }

    return 0; // 프로그램 정상 종료
}
