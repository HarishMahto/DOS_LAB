#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

// Function prototypes
void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int n, int m);
bool is_safe_state(int processes[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int n, int m, int safe_sequence[]);
bool can_grant_request(int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int max[][MAX_RESOURCES], int process_index, int request[], int m);

int main() {
    int n = 5; // Number of processes
    int m = 4; // Number of resources

    // Initial resource allocation and max data
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 0, 1, 2},
        {2, 0, 0, 0},
        {0, 0, 3, 4},
        {2, 3, 5, 4},
        {0, 3, 3, 2}
    };
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 0, 1, 2},
        {2, 7, 5, 0},
        {6, 6, 5, 6},
        {4, 3, 5, 6},
        {0, 6, 5, 2}
    };

    int available[MAX_RESOURCES] = {6, 7, 12, 12};

    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculate_need(need, max, allocation, n, m);

    // Print Need Matrix
    printf("Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check if the system is in a safe state
    int safe_sequence[MAX_PROCESSES];
    if (is_safe_state((int[]){0, 1, 2, 3, 4}, available, max, allocation, n, m, safe_sequence)) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    // Evaluate if P3 can request 1 more instance of R2
    int request[MAX_RESOURCES] = {0, 1, 0, 0};
    int process_index = 2; // P3

    if (can_grant_request(available, allocation, need, max, process_index, request, m)) {
        printf("Request from P%d can be granted immediately.\n", process_index + 1);
    } else {
        printf("Request from P%d cannot be granted immediately.\n", process_index + 1);
    }

    return 0;
}

// Calculate Need Matrix
void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Check if the system is in a safe state
bool is_safe_state(int processes[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int n, int m, int safe_sequence[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safe_sequence[count++] = processes[i];
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // System is not in a safe state
        }
    }
    return true;
}

// Check if a specific request can be granted
bool can_grant_request(int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int max[][MAX_RESOURCES], int process_index, int request[], int m) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process_index][i] || request[i] > available[i]) {
            return false;
        }
    }

    // Simulate granting the request
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process_index][i] += request[i];
        need[process_index][i] -= request[i];
    }

    // Check if the system remains in a safe state
    int safe_sequence[MAX_PROCESSES];
    bool is_safe = is_safe_state((int[]){0, 1, 2, 3, 4}, available, max, allocation, MAX_PROCESSES, MAX_RESOURCES, safe_sequence);

    // Rollback changes
    for (int i = 0; i < m; i++) {
        available[i] += request[i];
        allocation[process_index][i] -= request[i];
        need[process_index][i] += request[i];
    }

    return is_safe;
}
