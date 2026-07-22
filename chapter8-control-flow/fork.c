#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    pid_t pid = getpid();
    int x = 0;

    child_pid = fork();

    if (child_pid == 0) {
        while (1) {
            printf("Hello! I hope I'm not dead.\n");
        }
        exit(0);
    }

    printf("Parent... died\n");

    exit(0);
}
