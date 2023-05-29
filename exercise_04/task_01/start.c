#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <prog> <arguments>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }


    if (pid == 0) {
        setpriority(PRIO_PROCESS, pid, 19);
        execvp(argv[1], argv+1);
    }
    else {
        printf("PID: %d\n", pid);
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            printf("Return code: %d\n", WEXITSTATUS(wstatus));
        }
        if (WIFSIGNALED(wstatus)) {
            int signal = WTERMSIG(wstatus);
            printf("Signal: %d\n", signal);
        }
    }
}
