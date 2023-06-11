#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <string.h>

#define N_DATA 2000000
#define N_SHARED 2000
#define SEM_PRODUCER "/producer"
#define SEM_CONSUMER "/consumer"

int main()
{
    int i;
    key_t key = IPC_PRIVATE;
    int shm_id;
    int *shared_mem;

    // Semaphoren erstellen
    sem_t *sem_prod = sem_open(SEM_PRODUCER, O_CREAT, 0666, 1); // Schreiben erlaubt
    sem_t *sem_cons = sem_open(SEM_CONSUMER, O_CREAT, 0666, 0); // Lesen verboten

    // Shared Memory erstellen
    shm_id = shmget(key, N_SHARED * sizeof(int), IPC_CREAT | 0666);
    if (shm_id < 0)
    {
        perror("shmget");
        exit(1);
    }

    // Array mit int-Daten erstellen
    int *data = malloc(N_DATA * sizeof(int));
    srand48(getpid());
    for (i = 0; i < N_DATA; i++)
        data[i] = lrand48();

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid > 0)
    { // Vaterprozess
        for (i = 0; i < N_DATA; i += N_SHARED)
        {
            sem_wait(sem_prod); // P-Operation auf S2
            shared_mem = shmat(shm_id, NULL, 0);
            if (shared_mem == (int *)-1)
            {
                perror("shmat");
                exit(1);
            }

            // Daten in den Shared Memory kopieren
            memcpy(shared_mem, data + i, N_SHARED * sizeof(int));
            shmdt(shared_mem);

            sem_post(sem_cons); // V-Operation auf S1
        }

        wait(NULL); // auf Kindprozess warten

        // Aufräumen
        sem_unlink(SEM_PRODUCER);
        sem_unlink(SEM_CONSUMER);
        shmctl(shm_id, IPC_RMID, NULL);

        free(data);
    }
    else
    { // Kindprozess
        for (i = 0; i < N_DATA; i += N_SHARED)
        {
            sem_wait(sem_cons); // P-Operation auf S1
            shared_mem = shmat(shm_id, NULL, 0);
            if (shared_mem == (int *)-1)
            {
                perror("shmat");
                exit(1);
            }

            // Daten aus dem Shared Memory lesen
            // In diesem Beispiel werden die Daten einfach gedruckt
            for (int j = 0; j < N_SHARED; j++)
                printf("%d\n", shared_mem[j]);
            shmdt(shared_mem);

            sem_post(sem_prod); // V-Operation auf S2
        }
    }

    return 0;
}
