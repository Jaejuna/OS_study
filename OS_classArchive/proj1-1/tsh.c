/*
 * Copyright(c) 2023 All rights reserved by Heekuck Oh.
 * 이 프로그램은 한양대학교 ERICA 컴퓨터학부 학생을 위한 교육용으로 제작되었다.
 * 한양대학교 ERICA 학생이 아닌 이는 프로그램을 수정하거나 배포할 수 없다.
 * 프로그램을 수정할 경우 날짜, 학과, 학번, 이름, 수정 내용을 기록한다.
 * 23/03/29, 프랑스학과, 2017093772, 정재준, 표준 입출력과, 파이프 기능 추가 수정 합니다!
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80             /* 명령어의 최대 길이 */

/*
 * cmdexec - 명령어를 파싱해서 실행한다.
 * 스페이스와 탭을 공백문자로 간주하고, 연속된 공백문자는 하나의 공백문자로 축소한다. 
 * 작은 따옴표나 큰 따옴표로 이루어진 문자열을 하나의 인자로 처리한다.
 * 기호 '<' 또는 '>'를 사용하여 표준 입출력을 파일로 바꾸거나,
 * 기호 '|'를 사용하여 파이프 명령을 실행하는 것도 여기에서 처리한다.
 */
static void cmdexec(char *cmd)
{
    //명령어 인자 받기 위해 캐릭터 포인터 배열 argv 선언
    char *argv[MAX_LINE/2+1];
    // 카운트 변수 선언
    int argc = 0;
    // 명령어 스트링 파싱을 위한 캐릭터 포인터 선언
    char *p, *q;
    // 입출력 리다이랙션 선언, 초기화
    int in_fd = -1, out_fd = -1;
    // 파이프 기능 문자 추적을 위한 불리안 변수 선언
    bool pipe_found = false;
    // 파이프의 읽기, 쓰기를 위한 2개 정수를 담을 수 있는 배열 선언
    int pipefd[2];

    // p를 명령어 문자열 시작점을 포인팅, 띄어쓰기 탭 스킵하기
    p = cmd; p += strspn(p, " \t");
    // p가 null이 되면 do iterator 종료
    do {
        // 띄어쓰기, 탭 등 특별한 문자 검출
        q = strpbrk(p, " \t\'\"<>|");
        if (q == NULL || *q == ' ' || *q == '\t') {
            // 특별한 문자열 기준으로 separate
            q = strsep(&p, " \t");
            if (*q) argv[argc++] = q;
        }
        // 밑으로 standard input/output redirection, pipe handler
        else if (*q == '\'') {
            q = strsep(&p, "\'");
            if (*q) argv[argc++] = q;
            q = strsep(&p, "\'");
            if (*q) argv[argc++] = q;
        }
        else if (*q == '\"') {
            q = strsep(&p, "\"");
            if (*q) argv[argc++] = q;
            q = strsep(&p, "\"");
            if (*q) argv[argc++] = q;
        }
        else if (*q == '<') {
            q = strsep(&p, "<");
            p += strspn(p, " \t");
            q = strsep(&p, " \t");
            in_fd = open(q, O_RDONLY);
            if (in_fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        }
        else if (*q == '>') {
            q = strsep(&p, ">");
            p += strspn(p, " \t");
            q = strsep(&p, " \t");
            out_fd = open(q, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        }
        else if (*q == '|') {
            q = strsep(&p, "|");
            pipe_found = true;
            break;
        }

    } while (p);

    argv[argc] = NULL;

    // pipe 찾으면 pipe(pipfd) 배열에 읽기, 쓰기 저장 
    if (pipe_found) {
        if (pipe(pipefd) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // 새로운 자식 프로세스 fork로 만들기
    pid_t pid = fork();

    // 자식 프로세스가 execvp 실행, 예외 사항 적용
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        if (in_fd != -1) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != -1 && !pipe_found) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        if (pipe_found) {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
        }
        execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // 입출력 리다이렉션 닫기
    if (in_fd != -1) {
        close(in_fd);
    } 
}

/*
 * 기능이 간단한 유닉스 셸인 tsh (tiny shell)의 메인 함수이다.
 * tsh은 프로세스 생성과 파이프를 통한 프로세스간 통신을 학습하기 위한 것으로
 * 백그라운드 실행, 파이프 명령, 표준 입출력 리다이렉션 일부만 지원한다.
 */
int main(void)
{
    char cmd[MAX_LINE+1];       /* 명령어를 저장하기 위한 버퍼 */
    int len;                    /* 입력된 명령어의 길이 */
    pid_t pid;                  /* 자식 프로세스 아이디 */
    int background;             /* 백그라운드 실행 유무 */
    
    /*
     * 종료 명령인 "exit"이 입력될 때까지 루프를 무한 반복한다.
     */
    while (true) {
        /*
         * 좀비 (자식)프로세스가 있으면 제거한다.
         */
        pid = waitpid(-1, NULL, WNOHANG);
        if (pid > 0)
            printf("[%d] + done\n", pid);
        /*
         * 셸 프롬프트를 출력한다. 지연 출력을 방지하기 위해 출력버퍼를 강제로 비운다.
         */
        printf("tsh> "); fflush(stdout);
        /* 
         * 표준 입력장치로부터 최대 MAX_LINE까지 명령어를 입력 받는다.
         * 입력된 명령어 끝에 있는 새줄문자를 널문자로 바꿔 C 문자열로 만든다.
         * 입력된 값이 없으면 새 명령어를 받기 위해 루프의 처음으로 간다.
         */
        len = read(STDIN_FILENO, cmd, MAX_LINE);
        if (len == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        cmd[--len] = '\0';
        if (len == 0)
            continue;
        /*
         * 종료 명령이면 루프를 빠져나간다.
         */
        if(!strcasecmp(cmd, "exit"))
            break;
        /*
         * 백그라운드 명령인지 확인하고, '&' 기호를 삭제한다.
         */
        char *p = strchr(cmd, '&');
        if (p != NULL) {
            background = 1;
            *p = '\0';
        }
    else
            background = 0;
        /*
         * 자식 프로세스를 생성하여 입력된 명령어를 실행하게 한다.
         */
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        /*
         * 자식 프로세스는 명령어를 실행하고 종료한다.
         */
        else if (pid == 0) {
            cmdexec(cmd);
            exit(EXIT_SUCCESS);
        }
        /*
         * 포그라운드 실행이면 부모 프로세스는 자식이 끝날 때까지 기다린다.
         * 백그라운드 실행이면 기다리지 않고 다음 명령어를 입력받기 위해 루프의 처음으로 간다.
         */
        else if (!background)
            waitpid(pid, NULL, 0);
    }
    return 0;
}
