#include <stdio.h>

int main() {
    int n, i, j, start[20], length[20], block[50], k, flag;

    // Initialize all blocks as free (0 = free, 1 = allocated)
    for (i = 0; i < 50; i++) {
        block[i] = 0;
    }

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter starting block and length of file %d: ", i + 1);
        scanf("%d%d", &start[i], &length[i]);

        flag = 0;
        for (j = start[i]; j < start[i] + length[i]; j++) {
            if (block[j] == 1) { // block already allocated
                flag = 1;
                break;
            }
        }

        if (flag == 0) { 
            for (j = start[i]; j < start[i] + length[i]; j++) {
                block[j] = 1; // allocate blocks
            }
            printf("File %d allocated successfully.\n", i + 1);
        } 
        else {
            printf("File %d cannot be allocated. Some blocks are already in use.\n", i + 1);
        }
    }

    // Display allocation table
    printf("\nAllocation Table:\n");
    printf("File No.\tStart\tLength\tBlocks Allocated\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t", i + 1, start[i], length[i]);
        for (j = start[i]; j < start[i] + length[i]; j++) {
            if (block[j] == 1)
                printf("%d ", j);
        }
        printf("\n");
    }

    return 0;
}
