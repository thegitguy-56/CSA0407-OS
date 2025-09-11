#include <stdio.h>

int main() {
    int n, i, j;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n], waitingTime[n], turnaroundTime[n], process[n], priority[n];

    // Input burst times and priorities
    printf("Enter burst time and priority for each process:\n");
    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("P%d - Priority: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Sort processes by priority (smaller number = higher priority)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (priority[i] > priority[j]) {
                // swap priority
                int temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // swap burst time
                temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;

                // swap process IDs
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    // First process waiting time = 0
    waitingTime[0] = 0;

    // Calculate waiting times
    for (i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    // Calculate turnaround times
    for (i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        avgWT += waitingTime[i];
        avgTAT += turnaroundTime[i];
    }
    avgWT /= n;
    avgTAT /= n;

    // Display results
    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", process[i], priority[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);

    return 0;
}
