#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;

    // Get the process id of this (the parent) process.
    printf("Parent PID: %ld\n", (long)getpid());
    if ((pid = fork()) < 0) {
        fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    } else if (pid > 0) {
        // We're in the parent.
        // pid is the process id of the child.
        printf("Child PID: %ld\n", (long)pid);
        int status;
        do {
            // Wait for the child to complete, and get the status of how it
            // terminated.
            pid_t w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
            if (w == -1) {
                // waitpid failed.
                perror("waitpid()");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(status)) {
                printf("Child process %ld exited, status=%d.\n", (long)pid,
                       WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child process %ld killed by signal %d.\n", (long)pid,
                       WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("Child process %ld stopped by signal %d.\n", (long)pid,
                       WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("Child process %ld continued.\n", (long)pid);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        // We're in the child.
        // Execute a process, in this case, your pfind binary.
        if (execv("pfind", argv) == -1) {
            fprintf(stderr, "Error: execv() failed. %s.\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
