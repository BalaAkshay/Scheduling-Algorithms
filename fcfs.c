#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;       
    int arrival_time;   
    int burst_time;    
    int completion_time;
    int turnaround_time; 
    int waiting_time;    
};


int compareArrivalTime(const void *a, const void *b) {
    struct Process *processA = (struct Process *)a;
    struct Process *processB = (struct Process *)b;
    return processA->arrival_time - processB->arrival_time;
}

void calculateTimes(struct Process processes[], int n) {
    int current_time = 0; 

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time; 
        }
        
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;

        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;

        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        
    }
}

int main() {
    int n;
    int total_wait = 0, total_tat = 0;  

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d (Arrival Time, Burst Time): ", i + 1);
        processes[i].pid = i + 1; 
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    qsort(processes, n, sizeof(struct Process), compareArrivalTime);

    calculateTimes(processes, n);

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time);

        total_wait += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}                         
