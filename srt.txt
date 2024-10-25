#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int id, at, bt, rt;
} Process;

int compareArrival(const void *a, const void *b) {
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return processA->at - processB->at;
}

void srt(int n, Process *processes, double *avgWaitTime, double *avgTurnAroundTime) {
    qsort(processes, n, sizeof(Process), compareArrival);
    *avgWaitTime = 0;
    *avgTurnAroundTime = 0;
    int currentTime = processes[0].at;
    int i = 0, j = 0, prev = -1;
    printf("Gantt Chart: \n");

    while (i < n) {
        while (j < n && processes[j].at <= currentTime)
            j++;
        int minIndex = i;
        for (int k = i + 1; k < j; k++)
            if (processes[k].rt < processes[minIndex].rt)
                minIndex = k;
        if (minIndex != i) {
            Process temp = processes[i];
            processes[i] = processes[minIndex];
            processes[minIndex] = temp;
        }
        if (prev != processes[i].id) {
            printf("|\tP%d\t", processes[i].id);
            prev = processes[i].id;
        }
        int runTime = processes[i].rt;
        if (j < n)
            runTime = min(processes[minIndex].rt, processes[j].at - currentTime);
        processes[i].rt -= runTime;
        currentTime += runTime;
        if (processes[i].rt == 0) {
            *avgWaitTime += currentTime - processes[i].at - processes[i].bt;
            *avgTurnAroundTime += currentTime - processes[i].at;
            i++;
        }
    }
    printf("|\n");
    *avgWaitTime /= n;
    *avgTurnAroundTime /= n;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process *processes = (Process *)malloc(n * sizeof(Process));
    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].bt);
        processes[i].rt = processes[i].bt;
        processes[i].id = i;
    } 
    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &processes[i].at);
    double avgWaitTime, avgTurnAroundTime;
    srt(n, processes, &avgWaitTime, &avgTurnAroundTime);
    printf("Average Waiting Time: %.2lf\n", avgWaitTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnAroundTime);
    free(processes);
    return 0;
}