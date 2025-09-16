#include <stdio.h>

int main() {
    int n, i, tq, remaining;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n];

    printf("Enter burst times for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Remaining time initially = burst time
        wt[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int t = 0; // Current time
    remaining = n;

    while (remaining > 0) {
        int done = 1; // To check if all are done
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0; // At least one process is left
                if (rt[i] > tq) {
                    t += tq;
                    rt[i] -= tq;
                } else {
                    t += rt[i];
                    wt[i] = t - bt[i]; // Waiting time
                    rt[i] = 0;
                    remaining--;
                }
            }
        }
        if (done) break;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float avgWT = 0, avgTAT = 0;
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time
        avgWT += wt[i];
        avgTAT += tat[i];
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    avgWT /= n;
    avgTAT /= n;
    printf("\nAverage Waiting Time = %.2f", avgWT);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT);

    return 0;
}
