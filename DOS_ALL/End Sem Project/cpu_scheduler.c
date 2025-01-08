#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int id, arrival_time, burst_time, waiting_time, turnaround_time, response_time, remaining_time;
} Process;

// Function prototypes
void fcfs(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);
void print_gantt_chart_fcfs(Process processes[], int n);
void print_gantt_chart_rr(int gantt[], int size);

int main() {
    int choice, n, quantum;
    Process processes[MAX_PROCESSES];

    while (1) {
        printf("\nCPU Scheduling Simulator\n");
        printf("1. FCFS\n2. Round Robin\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        printf("Enter the number of processes: ");
        scanf("%d", &n);

        // Take all processes input at once
        printf("Enter Process ID, Arrival Time, and Burst Time for each process (format: ID Arrival Burst):\n");
        for (int i = 0; i < n; i++) {
            printf("Process %d: ", i + 1);
            scanf("%d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
            processes[i].remaining_time = processes[i].burst_time; // For RR
        }

        switch (choice) {
            case 1:
                fcfs(processes, n);
                break;
            case 2:
                printf("Enter time quantum: ");
                scanf("%d", &quantum);
                round_robin(processes, n, quantum);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

// FCFS implementation
void fcfs(Process processes[], int n) {
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time; // CPU idle time
        }
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
        processes[i].turnaround_time = current_time - processes[i].arrival_time;
        processes[i].response_time = processes[i].waiting_time;
    }

    print_gantt_chart_fcfs(processes, n);

    // Calculate averages
    float avg_wait = 0, avg_turn = 0, avg_resp = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += processes[i].waiting_time;
        avg_turn += processes[i].turnaround_time;
        avg_resp += processes[i].response_time;
    }
    printf("Average Waiting Time: %.2f\n", avg_wait / n);
    printf("Average Turnaround Time: %.2f\n", avg_turn / n);
    printf("Average Response Time: %.2f\n", avg_resp / n);
}

// Round Robin implementation
void round_robin(Process processes[], int n, int quantum) {
    int current_time = 0, completed = 0, gantt[MAX_PROCESSES * 10], gantt_size = 0;
    int queue[MAX_PROCESSES], front = 0, rear = 0;

    // Add processes to the queue in arrival order
    for (int i = 0; i < n; i++) {
        queue[rear++] = i;
    }

    while (completed < n) {
        int i = queue[front];
        front = (front + 1) % MAX_PROCESSES;

        if (processes[i].remaining_time > 0) {
            gantt[gantt_size++] = processes[i].id;

            if (processes[i].remaining_time > quantum) {
                current_time += quantum;
                processes[i].remaining_time -= quantum;
            } else {
                current_time += processes[i].remaining_time;
                processes[i].waiting_time = current_time - processes[i].arrival_time - processes[i].burst_time;
                processes[i].turnaround_time = current_time - processes[i].arrival_time;
                processes[i].response_time = processes[i].turnaround_time - processes[i].burst_time;
                processes[i].remaining_time = 0;
                completed++;
            }

            // Add to queue again if not completed
            if (processes[i].remaining_time > 0) {
                queue[rear++] = i;
            }
        }
    }

    print_gantt_chart_rr(gantt, gantt_size);

    // Calculate averages
    float avg_wait = 0, avg_turn = 0, avg_resp = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += processes[i].waiting_time;
        avg_turn += processes[i].turnaround_time;
        avg_resp += processes[i].response_time;
    }
    printf("Average Waiting Time: %.2f\n", avg_wait / n);
    printf("Average Turnaround Time: %.2f\n", avg_turn / n);
    printf("Average Response Time: %.2f\n", avg_resp / n);
}

// Gantt chart for FCFS
void print_gantt_chart_fcfs(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].id);
    }
    printf("|\n");
}

// Gantt chart for RR
void print_gantt_chart_rr(int gantt[], int size) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < size; i++) {
        printf("| P%d ", gantt[i]);
    }
    printf("|\n");
}
