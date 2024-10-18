#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;              
    int arrival_time;     
    int burst_time;       
    int remaining_time;   
    int completion_time;  
    int turnaround_time;  
    int waiting_time;     
};


void calculateTimes(struct Process processes[], int n, int time_quantum) {
    int current_time = 0; 
    int completed = 0; 

    while (completed < n) { 
        int all_done = 1; 
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                all_done = 0; 
                if (processes[i].arrival_time <= current_time) {
                    if (processes[i].remaining_time > time_quantum) {
                        current_time += time_quantum;
                        processes[i].remaining_time -= time_quantum;
                    } else {
                
                        current_time += processes[i].remaining_time;
                        processes[i].completion_time = current_time;
                        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                        processes[i].remaining_time = 0; 
                        completed++; 
                    }
                }
            }
        }
        
        if (all_done) {
            current_time++;
        }
    }
}

int main() {
    int n, time_quantum;
    int total_tat = 0, total_wait = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d (Arrival Time, Burst Time): ", i + 1);
        processes[i].pid = i + 1; 
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; 
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    calculateTimes(processes, n, time_quantum);

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
