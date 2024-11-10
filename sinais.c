#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
int done = 0;

void *waiting_thread(void *arg) {
    pthread_mutex_lock(&mutex);
    while (!done) {
        printf("Esperando pelo sinal...\n");
        pthread_cond_wait(&cond_var, &mutex);
    }
    printf("Sinal recebido!\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *signaling_thread(void *arg) {
    pthread_mutex_lock(&mutex);
    done = 1;
    pthread_cond_signal(&cond_var);
    printf("Sinal enviado!\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, waiting_thread, NULL);
    pthread_create(&t2, NULL, signaling_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
