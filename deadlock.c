#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resource1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource2 = PTHREAD_MUTEX_INITIALIZER;

void *process1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&resource1);
        printf("Proceso 1 adquirió el recurso 1\n");
        sleep(1);
        pthread_mutex_lock(&resource2);
        printf("Proceso 1 adquirió el recurso 2\n");
        pthread_mutex_unlock(&resource2);
        pthread_mutex_unlock(&resource1);
    }
    return NULL;
}

void *process2(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&resource2);
        printf("Proceso 2 adquirió el recurso 2\n");
        sleep(1);
        pthread_mutex_lock(&resource1);
        printf("Proceso 2 adquirió el recurso 1\n");
        pthread_mutex_unlock(&resource1);
        pthread_mutex_unlock(&resource2);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, process1, NULL);
    pthread_create(&t2, NULL, process2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}