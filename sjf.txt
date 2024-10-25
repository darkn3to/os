#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, bt, at, wt, tt, ct;
} Process;

void sjf(int n, Process *p, double *avg_wt, double *avg_tt) {
    int i, j;
    int total_wt = 0, total_tt = 0, time = 0, completed = 0;
    int done[n];
    for (i = 0; i < n; i++) {
        done[i] = 0;
    }
    printf("\nGantt Chart:\n");
    while (completed < n) {
        int min_index = -1;
        int min_bt = __INT_MAX__;
        for (i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                min_index = i;
            }
        }
        if (min_index != -1) {
            p[min_index].ct = time + p[min_index].bt;
            p[min_index].tt = p[min_index].ct - p[min_index].at;
            p[min_index].wt = p[min_index].tt - p[min_index].bt;
            total_wt += p[min_index].wt;
            total_tt += p[min_index].tt;
            printf("|\tP%d\t", p[min_index].id);
            time = p[min_index].ct;
            done[min_index] = 1;
            completed++;
        } 
        else {
            ++time;
        }
    }
    printf("|\n");
    *avg_wt = (double)total_wt / n;
    *avg_tt = (double)total_tt / n;
}


int main() {
    int n, end=0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process *processes = (Process *)malloc(n * sizeof(Process));
    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].bt);
        processes[i].id = i;
    }
    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].at);
    }
    double avgWaitTime, avgTurnAroundTime;
    sjf(n, processes, &avgWaitTime, &avgTurnAroundTime);
    printf("0\t");
    for (int i = 0; i < n; i++) {
        end += processes[i].bt;
        printf("\t%d\t", end);
    }
    printf("\n");
    printf("Average Waiting Time: %.2lf\n", avgWaitTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnAroundTime);
    free(processes);
    return 0;
}
