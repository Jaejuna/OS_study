#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 페이지내에 프레임 찾는 함수
int find(int page, int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++)
        if (page == frames[i])
            return 1;
    return 0;
}

//가장 오래 사용되지 않은 프레임 찾는 함수
int predict(int page_reference[], int frames[], int n_frames, int page_number, int n_pages) {
    int res = -1, farthest = page_number;
    for (int i = 0; i < n_frames; i++) {
        int j;
        for (j = page_number; j < n_pages; j++) {
            if (frames[i] == page_reference[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // 페이지가 미래에 사용되지 않을 시 반환
        if (j == n_pages)
            return i;
    }

    // 모든 프레임이 사용되지 않을 경우 아무거나 반환
    if (res == -1)
        return 0;
    else
        return res;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./optimal <number of page frames>\n");
        return -1;
    }

    // 프레임 수 선언
    int n_frames = atoi(argv[1]);
    int frames[n_frames];
    for (int i = 0; i < n_frames; i++)
        frames[i] = -1;

    // 페이지 수 범위 0~9
    int n_pages = 20;
    int page_reference[n_pages];
    for (int i = 0; i < n_pages; i++)
        page_reference[i] = rand() % 10;

    printf("Page Reference String:\n");
    for (int i = 0; i < n_pages; i++)
        printf("%d ", page_reference[i]);
    printf("\n");

    // 페이지 fault count
    int page_faults = 0;

    // OPT 알고리즘
    for (int i = 0; i < n_pages; i++) {
        if (!find(page_reference[i], frames, n_frames)) {
            int j = predict(page_reference, frames, n_frames, i + 1, n_pages);
            frames[j] = page_reference[i];
            page_faults++;
        }
    }

    printf("\nNumber of page faults: %d\n", page_faults);
    return 0;
}
