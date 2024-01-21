#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*simulate the concept of dining philosophers problem*/

#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5

pthread_t philosopher[NUM_PHILOSOPHERS];
pthread_mutex_t chopstick[NUM_CHOPSTICKS];

void dine(int n);

int main()
{
    int i, status_message;
    void *msg;

    // Initialize the mutex array
    for (i = 0; i < NUM_CHOPSTICKS; i++)
    {
        status_message = pthread_mutex_init(&chopstick[i], NULL);
        if (status_message != 0)
        {
            printf("\nMutex initialization failed");
            exit(1);
        }
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        status_message = pthread_create(&philosopher[i], NULL, (void *)dine, (void *)(intptr_t)i);
        if (status_message != 0)
        {
            printf("\nThread creation error\n");
            exit(1);
        }
    }

    // Wait for all philosopher threads to complete executing (finish dining)
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        status_message = pthread_join(philosopher[i], &msg);
        if (status_message != 0)
        {
            printf("\nThread join failed\n");
            exit(1);
        }
    }

    // Destroy the mutex array
    for (i = 0; i < NUM_CHOPSTICKS; i++)
    {
        status_message = pthread_mutex_destroy(&chopstick[i]);
        if (status_message != 0)
        {
            printf("\nMutex Destroyed\n");
            exit(1);
        }
    }

    return 0;
}

void dine(int n)
{
    printf("\nPhilosopher %d is thinking ", n);

    // Philosopher picks up the left chopstick (wait)
    pthread_mutex_lock(&chopstick[n]);

    // Philosopher picks up the right chopstick (wait)
    pthread_mutex_lock(&chopstick[(n + 1) % NUM_CHOPSTICKS]);

    // After picking up both chopsticks, philosopher starts eating
    printf("\nPhilosopher %d is eating ", n);
    sleep(3); // Simulating eating time

    // Philosopher places down the left chopstick (signal)
    pthread_mutex_unlock(&chopstick[n]);

    // Philosopher places down the right chopstick (signal)
    pthread_mutex_unlock(&chopstick[(n + 1) % NUM_CHOPSTICKS]);

    // Philosopher finishes eating
    printf("\nPhilosopher %d Finished eating ", n);
}