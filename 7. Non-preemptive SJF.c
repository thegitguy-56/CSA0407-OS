#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int bt;        // Burst Time
    int at;        // Arrival Time
    int wt;        // Waiting Time
    int tat;       // Turnaround Time
    int completed; // 0 = Not completed, 1 = Completed
};

int main() {
    int n, t = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    printf("\n--- Non-Preemptive SJF Scheduling ---\n");

    while (completed < n) {
        int idx = -1;
        int min_bt = 99999;

        // Select the process with shortest burst time among arrived & not completed
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].completed == 0 && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].wt = t - p[idx].at;           // Waiting Time
            p[idx].tat = p[idx].wt + p[idx].bt; // Turnaround Time

            avg_wt += p[idx].wt;
            avg_tat += p[idx].tat;

            t += p[idx].bt; // CPU executes this process fully
            p[idx].completed = 1;
            completed++;
        } else {
            // No process has arrived yet, move time forward
            t++;
        }
    }

    printf("\nPID\tAT\tBT\tWT\tTAT");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\n\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
