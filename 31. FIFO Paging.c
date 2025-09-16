#include <stdio.h>

int main() {
    int pages[30], frames[10], n, f, i, j, k, pageFaults = 0, next = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames as empty (-1 means empty)
    for (i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\nPage Reference String\tFrames\t\tPage Fault\n");

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in frame
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {  // Page fault occurs
            frames[next] = pages[i]; // Replace oldest page
            next = (next + 1) % f;   // Move to next frame (circular queue)
            pageFaults++;
        }

        // Print current frame status
        printf("%d\t\t\t", pages[i]);
        for (k = 0; k < f; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
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
