#include <stdio.h>

int main() {
    int nb, np, i, j;
    int bsize[20], psize[20], allocation[20];

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    printf("Enter size of each memory block:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &bsize[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &np);

    printf("Enter size of each process:\n");
    for (i = 0; i < np; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &psize[i]);
        allocation[i] = -1;  // initialize as not allocated
    }

    // First Fit Allocation
    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (bsize[j] >= psize[i]) { // block is big enough
                allocation[i] = j; // allocate block j to process i
                bsize[j] -= psize[i]; // reduce block size
                break; // go to next process
            }
        }
    }

    // Display Allocation Table
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
