#include <stdio.h>

int predict(int pages[], int frames[], int n, int index, int no_of_frames) {
    int farthest = index, pos = -1;
    for (int i = 0; i < no_of_frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n)  // Page not found in future
            return i;
    }
    if (pos == -1)
        return 0;  // If all pages will be used soon, replace first one
    else
        return pos;
}

int main() {
    int no_of_pages, no_of_frames, pages[30], frames[10];
    int pageFaults = 0, index = 0;

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter the page reference string: ");
    for (int i = 0; i < no_of_pages; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    for (int i = 0; i < no_of_frames; i++)
        frames[i] = -1;

    printf("\nPage Reference String\tFrames\t\tPage Fault\n");

    for (int i = 0; i < no_of_pages; i++) {
        int found = 0;

        // Check if page already in frame
        for (int j = 0; j < no_of_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (index < no_of_frames) {  // Empty frame available
                frames[index++] = pages[i];
            } else {
                int pos = predict(pages, frames, no_of_pages, i + 1, no_of_frames);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }

        // Print current frame contents
        printf("%d\t\t\t", pages[i]);
        for (int j = 0; j < no_of_frames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        if (!found)
            printf("\tPage Fault");
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
