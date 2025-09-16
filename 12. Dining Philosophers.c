#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
sem_t room; // semaphore to limit number of philosophers

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Wait for room (allow only 4 philosophers at a time)
        sem_wait(&room);

        // Pick up left chopstick
        pthread_mutex_lock(&chopsticks[id]);
        printf("Philosopher %d picked up left chopstick.\n", id);

        // Pick up right chopstick
        pthread_mutex_lock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right chopstick.\n", id);

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(2);

        // Put down right chopstick
        pthread_mutex_unlock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right chopstick.\n", id);

        // Put down left chopstick
        pthread_mutex_unlock(&chopsticks[id]);
        printf("Philosopher %d put down left chopstick.\n", id);

        // Signal room semaphore to let another philosopher try
        sem_post(&room);

        // Repeat
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Initialize semaphore to allow only 4 philosophers at a time
    sem_init(&room, 0, NUM_PHILOSOPHERS - 1);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (runs indefinitely, use Ctrl+C to stop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup (never reached in infinite simulation)
    sem_destroy(&room);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
