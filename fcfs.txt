#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, bt, at, wt, tt, ct;
} Process;

void fcfs(int n, Process *p, double *avg_wt, double *avg_tt) {
    int i;
    int total_wt = 0, total_tt = 0;
    p[0].ct = p[0].at + p[0].bt;
    p[0].tt = p[0].ct - p[0].at;
    p[0].wt = p[0].tt - p[0].bt;
    total_wt += p[0].wt;
    total_tt += p[0].tt;
    for (i = 1; i < n; i++) {
        p[i].ct = (p[i-1].ct > p[i].at ? p[i-1].ct : p[i].at) + p[i].bt;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        total_wt += p[i].wt;
        total_tt += p[i].tt;
    }
    *avg_wt = (double)total_wt / n;
    *avg_tt = (double)total_tt / n;
}
void print_gantt_chart(int n, Process *p) {
    int i;
    int end = 0;
    
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("|\tP%d\t", p[i].id);
    }
    printf("|\n");
    end = 0;
    printf("0\t");
    for (i = 0; i < n; i++) {
        end += p[i].bt;
        printf("\t%d\t", end);
    }
    printf("\n");
}

int main() {
    int n;
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
    fcfs(n, processes, &avgWaitTime, &avgTurnAroundTime);
    print_gantt_chart(n, processes);
    printf("Average Waiting Time: %.2lf\n", avgWaitTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnAroundTime);
    free(processes);
    return 0;
}
