#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;

void *reader(void *arg) {
    pthread_mutex_lock(&read_count_mutex);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&resource_mutex);
    }
    pthread_mutex_unlock(&read_count_mutex);

    printf("Thread leitora %ld lendo\n", (long)arg);
    sleep(2);

    pthread_mutex_lock(&read_count_mutex);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&resource_mutex);
    }
    pthread_mutex_unlock(&read_count_mutex);

    return NULL;
}

void *writer(void *arg) {
    pthread_mutex_lock(&resource_mutex);

    printf("Thread escritora %ld escrevendo\n", (long)arg);
    sleep(1);

    pthread_mutex_unlock(&resource_mutex);

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];

    for (long i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)i);
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    return 0;
}