#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Process {
    int pid;       
    int arrival_time;   
    int burst_time;    
    int completion_time;
    int turnaround_time; 
    int waiting_time;    
    int remaining_time;
};

int findShortestJob(struct Process processes[], int n, int current_time) {
    int shortest_idx = -1;
    int shortest_time = INT_MAX; 
    
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < shortest_time) {
            shortest_time = processes[i].remaining_time;
            shortest_idx = i;
        }
    }
    
    return shortest_idx;
}

void calculateTimes(struct Process processes[], int n) {
    int current_time = 0, completed = 0;

    while (completed != n) {
        int shortest_idx = findShortestJob(processes, n, current_time);
        
        if (shortest_idx == -1) {
            current_time++;
            continue;
        }
        
        processes[shortest_idx].remaining_time--;

        if (processes[shortest_idx].remaining_time == 0) {
            completed++;
            processes[shortest_idx].completion_time = current_time + 1;
            processes[shortest_idx].turnaround_time = processes[shortest_idx].completion_time - processes[shortest_idx].arrival_time;
            processes[shortest_idx].waiting_time = processes[shortest_idx].turnaround_time - processes[shortest_idx].burst_time;

          
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
        printf("Enter details for Process %d (Arrival Time, Burst Time): ", i + 1);
        processes[i].pid = i + 1; 
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; 
    }

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

    printf("\nAverage Waiting Time: %.2f", (float)total_wait / n);
    printf(" | Average Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}