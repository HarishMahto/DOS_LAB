#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

// Function to check if a number is prime
bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Function to generate Fibonacci series
void generate_fibonacci(int *fib, int length) {
    if (length >= 1) fib[0] = 0;
    if (length >= 2) fib[1] = 1;
    for (int i = 2; i < length; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main() {
    pid_t pid;
    int length;

    // Get the length of Fibonacci series from user
    printf("Enter the length of Fibonacci series: ");
    scanf("%d", &length);

    if (length <= 0) {
        printf("Invalid length. Must be a positive integer.\n");
        exit(1);
    }

    int fib[length]; // Array to store the Fibonacci series
    int pipefd[2];   // Pipe for communication between parent and child

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: Generate Fibonacci series
        close(pipefd[0]); // Close reading end of the pipe
        generate_fibonacci(fib, length);
        write(pipefd[1], fib, sizeof(fib)); // Write Fibonacci series to pipe
        close(pipefd[1]); // Close writing end of the pipe
        printf("Child process (PID = %d) completed.\n", getpid());
        exit(0);
    } else {
        // Parent process: Wait for the child and process the data
        close(pipefd[1]); // Close writing end of the pipe
        wait(NULL);       // Wait for child process to complete

        read(pipefd[0], fib, sizeof(fib)); // Read Fibonacci series from pipe
        close(pipefd[0]); // Close reading end of the pipe

        // Display the Fibonacci series
        printf("Parent process (PID = %d): Fibonacci series:\n", getpid());
        for (int i = 0; i < length; i++) {
            printf("%d ", fib[i]);
        }
        printf("\n");

        // Display prime Fibonacci numbers with their positions
        printf("Prime Fibonacci numbers in the series:\n");
        for (int i = 0; i < length; i++) {
            if (is_prime(fib[i])) {
                printf("Position %d: %d\n", i + 1, fib[i]);
            }
        }

        printf("Parent process completed.\n");
    }

    return 0;
}
