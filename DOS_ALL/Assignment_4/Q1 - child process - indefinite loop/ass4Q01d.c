#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid == -1) {
        // Error handling if fork() fails
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        while (1) {
            printf("Child Process: PID = %d\n", getpid());
            sleep(1);  // Sleep to simulate indefinite execution
        }
    } 
    else {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());
        wait(NULL);  // Wait for the child process to complete
        printf("Parent: Child process has completed.\n");
    }

    return 0;
}
