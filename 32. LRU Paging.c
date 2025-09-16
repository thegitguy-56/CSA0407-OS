#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10];
    int flag1, flag2, i, j, pos, pageFaults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter the page reference string: ");
    for (i = 0; i < no_of_pages; ++i)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    // Initialize frames
    for (i = 0; i < no_of_frames; ++i)
        frames[i] = -1;

    printf("\nPage Reference String\tFrames\t\tPage Fault\n");

    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        // Check if page is already in frame
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter; // Update time for recently used page
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            // Find empty frame
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) { // No empty frame found => Replace LRU page
            pos = findLRU(time, no_of_frames);
            counter++;
            pageFaults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Print current frame status
        printf("%d\t\t\t", pages[i]);
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        if (flag1 == 0)
            printf("\tPage Fault");
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
