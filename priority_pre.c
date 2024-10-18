#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid;              
    int arrival_time;     
    int burst_time;       
    int completion_time;
    int turnaround_time;  
    int waiting_time;     
    int remaining_time;   
    int priority; 
    int completed;        
};

int findHighestPriority(struct Process processes[], int n, int current_time) {
    int highest_priority_idx = -1;
    int highest_priority = INT_MAX; 

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
            if (processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_idx = i;
            }
        }
    }

    return highest_priority_idx;
}

void calculateTimes(struct Process processes[], int n) {
    int current_time = 0; 
    int completed = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed < n) {
        int idx = findHighestPriority(processes, n, current_time);
        
        if (idx == -1) {
            current_time++;
            continue;
        }

        processes[idx].remaining_time--;

        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time + 1;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        }

        current_time++; 
    }
}

int main() {
    int n;
    int total_wait = 0, total_tat = 0; 

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d (Arrival Time, Burst Time, Priority): ", i + 1);
        processes[i].pid = i + 1; 
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    calculateTimes(processes, n);

    printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].priority,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time);

        total_wait += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wait / n);
    printf(" | Average Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}
