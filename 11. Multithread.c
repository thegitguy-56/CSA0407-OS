#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // for sleep()

// Function executed by Thread 1
void* thread_function_1(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 1: Count %d\n", i);
        sleep(1);  // Simulate work
    }
    pthread_exit(NULL);
}

// Function executed by Thread 2
void* thread_function_2(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 2: Count %d\n", i);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;  // Thread identifiers

    // Create two threads
    if (pthread_create(&t1, NULL, thread_function_1, NULL) != 0) {
        perror("Failed to create Thread 1");
        return 1;
    }

    if (pthread_create(&t2, NULL, thread_function_2, NULL) != 0) {
        perror("Failed to create Thread 2");
        return 1;
    }

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads finished execution.\n");
    return 0;
}
