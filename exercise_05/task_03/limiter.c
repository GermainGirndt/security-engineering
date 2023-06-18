#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

void handle_signal(int signal)
{
    switch (signal)
    {
    case SIGXCPU:
        printf("Received SIGXCPU: CPU time limit exceeded\n");
        break;
    case SIGSEGV:
        printf("Received SIGSEGV: Segmentation fault (possibly stack size limit exceeded)\n");
        break;
    case SIGXFSZ:
        printf("Received SIGXFSZ: File size limit exceeded\n");
        break;
    default:
        printf("Received signal %d\n", signal);
        break;
    }
    exit(EXIT_FAILURE);
}

void set_limit(int resource, rlim_t value)
{
    struct rlimit limit;
    limit.rlim_cur = value;
    limit.rlim_max = value;
    if (setrlimit(resource, &limit) < 0)
    {
        perror("setrlimit failed");
        exit(EXIT_FAILURE);
    }
}

int recursive_func()
{
    // Exceed stack size limit with infinite recursion
    return recursive_func();
}

int main()
{
    // Set CPU time limit
    set_limit(RLIMIT_CPU, 100); // seconds

    // Set stack size limit
    set_limit(RLIMIT_STACK, 1024 * 1024); // bytes (1 MB)

    // Set file size limit
    set_limit(RLIMIT_FSIZE, 1024); // bytes (1 KB)

    // Set signal handlers for the corresponding signals
    if (signal(SIGXCPU, handle_signal) == SIG_ERR)
    { // CPU limit exceeded
        perror("Failed to set signal handler for SIGXCPU");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGSEGV, handle_signal) == SIG_ERR)
    { // Stack size limit exceeded
        perror("Failed to set signal handler for SIGSEGV");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGXFSZ, handle_signal) == SIG_ERR)
    { // File size limit exceeded
        perror("Failed to set signal handler for SIGXFSZ");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to exceed CPU limit
    while (1)
    {

        // Exceed stack size limit
        recursive_func();

        // Exceed stack size limit
        FILE *f = fopen("test.txt", "w");
        if (f == NULL)
        {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 1024 * 1024; i++)
        {
            fputc('A', f);
        }
        fclose(f);
    };

    return 0;
}
