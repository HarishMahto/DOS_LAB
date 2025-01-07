#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

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
        while (1) {
            printf("Parent Process: PID = %d\n", getpid());
            sleep(1);  // Sleep to simulate indefinite execution
        }
    }

    return 0;
}
