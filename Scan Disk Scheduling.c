#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i, j, head, size, direction;
    int request[50], seek = 0, distance;

    printf("Enter total number of cylinders: ");
    scanf("%d", &size);

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter head movement direction (0 = towards 0, 1 = towards %d): ", size - 1);
    scanf("%d", &direction);

    // Add head and boundary (0 and size-1) to the request array
    request[n] = head;
    n++;
    request[n] = 0;
    n++;
    request[n] = size - 1;
    n++;

    // Sort the requests
    sort(request, n);

    // Find the index of the head
    int idx;
    for (i = 0; i < n; i++) {
        if (request[i] == head) {
            idx = i;
            break;
        }
    }

    printf("\nSequence of head movement:\n");
    printf("%d", head);

    // Move in the selected direction
    if (direction == 1) {
        // Move right first, then left
        for (i = idx + 1; i < n; i++) {
            distance = abs(request[i] - head);
            seek += distance;
            head = request[i];
            printf(" -> %d", head);
        }
        // Then move left
        for (i = idx - 1; i >= 0; i--) {
            distance = abs(request[i] - head);
            seek += distance;
            head = request[i];
            printf(" -> %d", head);
        }
    } else {
        // Move left first, then right
        for (i = idx - 1; i >= 0; i--) {
            distance = abs(request[i] - head);
            seek += distance;
            head = request[i];
            printf(" -> %d", head);
        }
        // Then move right
        for (i = idx + 1; i < n; i++) {
            distance = abs(request[i] - head);
            seek += distance;
            head = request[i];
            printf(" -> %d", head);
        }
    }

    printf("\n\nTotal Seek Time = %d\n", seek);

    return 0;
}
