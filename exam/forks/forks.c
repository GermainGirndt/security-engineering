#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;
    int a = 0;
    pid = fork();
    if (pid == 0)
    {
        a = a + 1;
        printf("PID %d, Ausgabe 1: %d\n", pid, a);
    }
    pid = fork();
    a = a + 2;
    printf("PID %d, Ausgabe 2: %d\n", pid, a);
    if (pid == 0)
    {
        a = a + 3;
        printf("PID %d, Ausgabe 3: %d\n", pid, a);
    }
    printf("PID %d, Ausgabe 4: %d\n", pid, a);
    return 0;
}
