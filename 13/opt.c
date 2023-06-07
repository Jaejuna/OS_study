#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the page in frames
int find(int page, int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++)
        if (page == frames[i])
            return 1;
    return 0;
}

// Function to find the frame that will not be used for the longest duration
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

        // If a page is never referenced in future, return it.
        if (j == n_pages)
            return i;
    }

    // If all of the frames were not in the future, return any of them
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

    // Initialize number of frames
    int n_frames = atoi(argv[1]);
    int frames[n_frames];
    for (int i = 0; i < n_frames; i++)
        frames[i] = -1;

    // Page numbers range from 0 to 9
    int n_pages = 20;
    int page_reference[n_pages];
    for (int i = 0; i < n_pages; i++)
        page_reference[i] = rand() % 10;

    printf("Page Reference String:\n");
    for (int i = 0; i < n_pages; i++)
        printf("%d ", page_reference[i]);
    printf("\n");

    // Count the number of page faults
    int page_faults = 0;

    // Start the OPT algorithm
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
