#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

// Size of the shared data chunk.
#define N_SHARED 2 // comment by submiting exercise
// #define N_SHARED 2000 // remove comment by submitting exercise

// Size of the data array.
#define N_DATA 10 // comment by submitting exercise
// #define N_DATA 2000000 // remove comment by submitting exercise

int data[N_DATA];

// sembuf for the producer_v (P1) and the consumer_p (P2)
struct sembuf producer_v, producer_p, consumer_v, consumer_p;

int main()
{
    int SEED = 65;
    int SHARED_MEMORY_SIZE = 1024; // bytes
    int SHARED_MEMORY_PERMISSIONS = 0666 | IPC_CREAT;
    int NUMBER_OF_SEMAPHORES_TO_CREATE = 2;

    key_t key = ftok("/dev\null", SEED);
    srand48(SEED);
    int shmid = shmget(key, SHARED_MEMORY_SIZE, SHARED_MEMORY_PERMISSIONS);
    int *shared_memory_pointer = (int *)shmat(shmid, (void *)0, 0); // Attach shared memory to the num pointer

    printf("Generating random values for data: \n");
    for (int i = 0; i < N_DATA; i++)
    {
        int random_num = lrand48() % ((unsigned int)INT_MAX + 1);
        printf("Position: %d - Random Value: %d\n", i, random_num);
        data[i] = random_num;
    }
    printf("\n");

    // Create semaphores
    int semid = semget(IPC_PRIVATE, NUMBER_OF_SEMAPHORES_TO_CREATE, SHARED_MEMORY_PERMISSIONS);
    if (semid < 0)
    {
        perror("Semget failed.");
        fflush(stdout);
        exit(1);
    }

    // S1 - Producer
    int PRODUCER_SEMAPHORE_NUMBER = 0;
    int PRODUCER_SEMAPHORE_INITIAL_VALUE = 1;
    semctl(semid, PRODUCER_SEMAPHORE_NUMBER, SETVAL, PRODUCER_SEMAPHORE_INITIAL_VALUE);
    // Initialize sembuf producer_v
    producer_p.sem_num = PRODUCER_SEMAPHORE_NUMBER; // semaphore number
    producer_p.sem_op = -1;                         // increase opeartion
    producer_p.sem_flg = 0;                         // flag
    producer_v.sem_num = PRODUCER_SEMAPHORE_NUMBER; // semaphore number
    producer_v.sem_op = 1;                          // increase opeartion
    producer_v.sem_flg = 0;                         // flag

    // S2 - Consumer
    int CONSUMER_SEMAPHORE_NUMBER = 1;
    int CONSUMER_SEMAPHORE_INITIAL_VALUE = 0;
    semctl(semid, CONSUMER_SEMAPHORE_NUMBER, SETVAL, CONSUMER_SEMAPHORE_INITIAL_VALUE);
    // Initialize sembuf consumer_p
    consumer_p.sem_num = CONSUMER_SEMAPHORE_NUMBER; // semaphore number
    consumer_p.sem_op = -1;                         // decrease operation
    consumer_p.sem_flg = 0;                         // flag
    consumer_v.sem_num = CONSUMER_SEMAPHORE_NUMBER; // semaphore number
    consumer_v.sem_op = 1;                          // decrease operation
    consumer_v.sem_flg = 0;                         // flag

    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child process (Consumer)\n");

        int total_operations_consumer = 0;
        while (total_operations_consumer < N_DATA)
        {
            semop(semid, &consumer_p, 1);

            printf("--- Consumer\n");
            for (int i = 0; i < N_SHARED; i++)
            {
                printf("Position in Shared Memory: %d - Value: %d - Total Operations: %d\n", i, shared_memory_pointer[i], total_operations_consumer);
                total_operations_consumer++;
            }
            printf("\n");

            semop(semid, &producer_v, 1);
        }
    }
    else
    {

        printf("Parent Process P1 (Producer)\n");

        int total_operations_producer = 0;

        while (total_operations_producer < N_DATA)
        {
            semop(semid, &producer_p, 1); // P operation on S2, 1 is the number of operations to be performed.
            printf("--- Producer\n");
            for (int i = 0; i < N_SHARED; i++)
            {
                int random_num_in_file = data[total_operations_producer];
                printf("Position in Shared Memory: %d - Value: %d - Total Operations: %d\n", i, random_num_in_file, total_operations_producer);
                shared_memory_pointer[i] = random_num_in_file;
                total_operations_producer++;
            }
            printf("\n");
            semop(semid, &consumer_v, 1); // V operation on S1, 1 is the number of operations to be performed.
        }

        // clean ups
        // (are executed by the parent process (for being sure that they are executed only once)
        semop(semid, &producer_p, 1);
        // Cleanup shared memory and semaphores
        shmdt(shared_memory_pointer); // Detach the shared memory
        // IPC_RMID is the command to remove the shared memory and semaphore.
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID, NULL);
        semctl(semid, 1, IPC_RMID, NULL);

        printf("Ending process with ID %d\n", pid);
    }

    return 0;
}
