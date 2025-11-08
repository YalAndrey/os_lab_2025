
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int factor=1;

struct Rang {
int begin;
int end;
int mod;
};


void functionfactor (const struct Rang *args) 
{
    for (int i = args->begin; i < args->end; i++) 
    {
    pthread_mutex_lock( &mutex1 );
    factor = factor * i;
    pthread_mutex_unlock( &mutex1 );
    }
    pthread_mutex_lock( &mutex1 );
    factor = factor % args->mod;
    pthread_mutex_unlock( &mutex1 );
}


int main() {
    int k = 8;
    int threads_num  = 4;
    int mod = 10;

    pthread_t threads[threads_num];
    struct Rang args[threads_num];
    int cell = k / threads_num;


    for (int i = 0; i < threads_num; i++) {
    args[i].mod = mod;
    args[i].begin = i * cell + 1;
    args[i].end = (i == threads_num - 1) ? k + 1 : (i + 1) * cell + 1;
    if (pthread_create(&threads[i], NULL, functionfactor, (void *)&args[i])) {
    printf("Error: pthread_create failed!\n");
    return 1;
    }
    }

    for (int i = 0; i < threads_num; i++) 
        pthread_join(threads[i], NULL);
    
    printf("Результат %d \n", factor);
    return 0;

}


/* Function C */
