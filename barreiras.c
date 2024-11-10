#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

pthread_barrier_t barrier;  // Declaração da barreira

void* thread_func(void* arg) {
    long id = (long)arg;

    printf("Thread %ld chegando na barreira\n", id);

    // A thread chega na barreira e aguarda as outras
    pthread_barrier_wait(&barrier);

    printf("Thread %ld passou pela barreira\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // Inicializa a barreira com o número de threads
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Cria as threads
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    // Espera que todas as threads alcancem a barreira
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroi a barreira após o uso
    pthread_barrier_destroy(&barrier);

    return 0;
}
