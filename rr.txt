#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *arr;
    int capacity, size, front, rear;
} queue;

void intialize(queue *q, int cap)
{
    q->capacity = cap;
    q->size = 0;
    q->front = q->rear = -1;
    q->arr = (int *)malloc(sizeof(int) * cap);
}

void enque(queue *q, int val)
{
    if (((q->rear + 1) % (q->capacity)) == q->front)
        return;
    q->rear = (q->rear + 1) % (q->capacity);
    if (q->front == -1)
        q->front = 0;
    q->arr[q->rear] = val;
    q->size++;
}

void deque(queue *q)
{
    if (q->front == -1)
        return;
    q->front = (q->front + 1) % (q->capacity);
    if (q->front == (q->rear + 1) % (q->capacity))
        q->front = q->rear = -1;
    q->size--;
}

int front(queue *q)
{
    if (q->size == 0)
        return -1;
    return q->arr[q->front];
}

void freeQueue(queue *q)
{
    free(q->arr);
    q->arr = NULL;
}

typedef struct
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
} Process;
int compareArrival(const void *a, const void *b)
{
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return processA->arrivalTime - processB->arrivalTime;
}
#define min(a, b) ((a) < (b) ? (a) : (b))
void roundRobin(int n, Process *processes, double *avgWaitTime, double *avgTurnAroundTime, int timeQuantum)
{
    for (int i = 0; i < n; i++)
        processes[i].remainingTime = processes[i].burstTime;
    qsort(processes, n, sizeof(Process), compareArrival);
    *avgWaitTime = 0;
    *avgTurnAroundTime = 0;
    queue q;
    intialize(&q, n);
    int currentTime = processes[0].arrivalTime;
    int prev = -1;
    int completed = 0;
    int j = 1;
    enque(&q, 0);
    printf("Round Robin Gantt Chart: ");
    while (completed < n)
    {
        if (q.size == 0)
        {
            currentTime = processes[j].arrivalTime;
            enque(&q, j++);
            continue;
        }
        int i = front(&q);
        deque(&q);
        if (prev != processes[i].id)
        {
            printf("P%d ", processes[i].id);
            prev = processes[i].id;
        }
        int runTime = min(processes[i].remainingTime, timeQuantum);
        processes[i].remainingTime -= runTime;
        currentTime += runTime;
        while (j < n && processes[j].arrivalTime <= currentTime)
            enque(&q, j++);
        if (processes[i].remainingTime == 0)
        {
            *avgWaitTime += currentTime - processes[i].arrivalTime - processes[i].burstTime;
            *avgTurnAroundTime += currentTime - processes[i].arrivalTime;
            completed++;
        }
        else
            enque(&q, i);
    }
    freeQueue(&q);
    printf("\n");
    *avgWaitTime /= n;
    *avgTurnAroundTime /= n;
}
int main()
{
    int n, timeQuantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process *processes = (Process *)malloc(n * sizeof(Process));
    printf("Enter burst times: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processes[i].burstTime);
        processes[i].id = i;
    }
    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &processes[i].arrivalTime);
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);
    double avgWaitTime, avgTurnAroundTime;
    roundRobin(n, processes, &avgWaitTime, &avgTurnAroundTime, timeQuantum);
    printf("Average Waiting Time: %.2lf\n", avgWaitTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnAroundTime);
    free(processes);
    return 0;
}