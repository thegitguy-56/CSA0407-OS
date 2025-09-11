#include <stdio.h>
#include <unistd.h>   // for fork(), getpid(), getppid()

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // fork failed
        printf("Fork failed!\n");
    } 
    else if (pid == 0) {
        // Child process
        printf("\n--- Child Process ---\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());
    } 
    else {
        // Parent process
        printf("\n--- Parent Process ---\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);
    }

    return 0;
}
