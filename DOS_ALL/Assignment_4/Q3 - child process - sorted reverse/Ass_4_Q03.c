#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void copy_file_content(const char *source, const char *destination) {
    FILE *src = fopen(source, "r");
    FILE *dest = fopen(destination, "w");

    if (!src || !dest) {
        perror("Error opening files");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), src)) {
        fputs(buffer, dest);
    }

    fclose(src);
    fclose(dest);
}

void display_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void display_sorted_content_reverse(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    // Read file lines into an array
    char *lines[100];
    char buffer[256];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        lines[count] = strdup(buffer);
        count++;
    }
    fclose(file);

    // Sort lines in reverse order
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(lines[i], lines[j]) < 0) {
                char *temp = lines[i];
                lines[i] = lines[j];
                lines[j] = temp;
            }
        }
    }

    // Print lines in reverse order
    printf("Sorted content in reverse order:\n");
    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
}

int main() {
    pid_t pid1, pid2, pid3;

    printf("Parent process started, PID = %d\n", getpid());

    // First child: Copy file1 to file2
    if ((pid1 = fork()) == 0) {
        printf("First child started, PID = %d, Parent PID = %d\n", getpid(), getppid());
        copy_file_content("file1.txt", "file2.txt");
        printf("First child completed: File content copied.\n");
        exit(0);
    }

    sleep(1); // Delay for parent

    // Second child: Display content of file2
    if ((pid2 = fork()) == 0) {
        printf("Second child started, PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Content of file2:\n");
        display_file_content("file2.txt");
        printf("Second child completed: Content displayed.\n");
        exit(0);
    }

    sleep(1); // Delay for parent

    // Third child: Display sorted content of file2 in reverse order
    if ((pid3 = fork()) == 0) {
        printf("Third child started, PID = %d, Parent PID = %d\n", getpid(), getppid());
        display_sorted_content_reverse("file2.txt");
        printf("Third child completed: Sorted content displayed in reverse order.\n");
        exit(0);
    }

    sleep(1); // Delay for parent

    // Parent process waits for all children
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent process completed, PID = %d\n", getpid());

    return 0;
}
