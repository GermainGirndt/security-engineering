#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>

#define N_DATA 2000000
#define N_SHARED 2000

int shmid, semid;
int *shm;
struct sembuf sem_op;

int main()
{
    key_t key = 1234;
    size_t size = N_SHARED * sizeof(int);
    int shmflg = IPC_CREAT | 0666;
    int semflg = IPC_CREAT | IPC_EXCL | 0666;

    /* Ein Shared-Memory-Segment wird erstellt, key ist ein eindeutiger Identifier */
    if ((shmid = shmget(key, size, shmflg)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    /* Das Shared-Memory-Segment wird an den Adressraum angefügt */
    if ((shm = shmat(shmid, NULL, 0)) == (int *)-1)
    {
        perror("shmat");
        exit(1);
    }

    /* Es werden 2 Semaphoren erstellt */
    if ((semid = semget(key, 2, semflg)) < 0)
    {
        perror("semget");
        exit(1);
    }

    printf("here");
    /* Initialisieren der Semaphore S2 um den Schreibzugriff zu erlauben */
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    if (semop(semid, &sem_op, 1) == -1)
    {
        perror("semop: semop failed");
        exit(1);
    }

    /* Erzeugen eines neuen Prozesses */
    int pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        /* Dieser Codeblock wird vom Kindprozess (P2, Verbraucher) ausgeführt */

        int j = 0;
        while (j < N_DATA)
        {
            /* Anforderung des Lesezugriffs */
            sem_op.sem_num = 0;
            sem_op.sem_op = -1;
            semop(semid, &sem_op, 1);

            /* Lesen aus dem Shared-Memory-Segment und Fortschreiten bis zum Ende der Daten */
            for (int i = 0; i < N_SHARED && j < N_DATA; i++, j++)
            {
                printf("Lesen: %d\n", shm[i]);
            }

            /* Freigabe des Schreibzugriffs */
            sem_op.sem_num = 1;
            sem_op.sem_op = 1;
            semop(semid, &sem_op, 1);
        }
    }
    else
    {
        /* Dieser Codeblock wird vom Elternprozess (P1, Erzeuger) ausgeführt */

        srand48(time(0));

        int j = 0;
        while (j < N_DATA)
        {
            /* Anforderung des Schreibzugriffs */
            sem_op.sem_num = 1;
            sem_op.sem_op = -1;
            semop(semid, &sem_op, 1);

            /* Schreiben in das Shared-Memory-Segment und Fortschreiten bis zum Ende der Daten */
            for (int i = 0; i < N_SHARED && j < N_DATA; i++, j++)
            {
                shm[i] = lrand48();
                printf("Schreiben: %d\n", shm[i]);
            }

            /* Freigabe des Lesezugriffs */
            sem_op.sem_num = 0;
            sem_op.sem_op = 1;
            semop(semid, &sem_op, 1);
        }
    }

    /* Löschen des Shared-Memory-Segments */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(1);
    }

    /* Löschen der Semaphoren */
    if (semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl");
        exit(1);
    }

    return 0;
}
