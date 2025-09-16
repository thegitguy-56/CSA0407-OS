#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int priority;   // Priority (Lower number = Higher priority)
    int rt;         // Remaining Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
};

int main() {
    int n, completed = 0, t = 0, i;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time, Burst Time, and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
    }

    printf("\n--- Pre-emptive Priority Scheduling ---\n");

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Select process with highest priority (lowest number) that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].rt > 0 && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].rt--;  // Execute process for 1 unit

            if (p[idx].rt == 0) {
                completed++;
                int finish_time = t + 1;
                p[idx].tat = finish_time - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                avg_wt += p[idx].wt;
                avg_tat += p[idx].tat;
            }
        }
        t++;
    }

    printf("\nPID\tAT\tBT\tPriority\tWT\tTAT");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t\t%d\t%d", p[i].pid, p[i].at, p[i].bt,
               p[i].priority, p[i].wt, p[i].tat);
    }

    printf("\n\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
