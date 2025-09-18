#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i;
    int request[50], seek = 0, distance;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSequence of head movement:\n");
    printf("%d", head);

    // Calculate total seek time
    for (i = 0; i < n; i++) {
        distance = abs(request[i] - head);
        seek += distance;
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal Seek Time = %d\n", seek);
    printf("Average Seek Time = %.2f\n", (float)seek / n);

    return 0;
}
