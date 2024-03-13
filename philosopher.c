#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define PENSAR 0
#define HAMBRIENTO 1
#define COMER 2

sem_t tenedores[NUM_FILOSOFOS];
int estado[NUM_FILOSOFOS];

void *filosofo(void *arg)
{
    int id = *(int *)arg;
    int izquierda = id;
    int derecha = (id + 1) % NUM_FILOSOFOS;

    while (1)
    {
        printf("Filósofo %d está pensando.\n", id);
        sleep(rand() % 3);

        printf("Filósofo %d tiene hambre.\n", id);
        estado[id] = HAMBRIENTO;

        // Intentar tomar los tenedores
        sem_wait(&tenedores[izquierda]);
        sem_wait(&tenedores[derecha]);

        // Comer
        printf("Filósofo %d está comiendo.\n", id);
        estado[id] = COMER;
        sleep(rand() % 3);

        sem_post(&tenedores[izquierda]);
        sem_post(&tenedores[derecha]);
        estado[id] = PENSAR;
    }
}

int main()
{
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    // Inicializar los semáforos
    for (int i = 0; i < NUM_FILOSOFOS; i++)
    {
        sem_init(&tenedores[i], 0, 1);
    }

    // Crear los hilos de los filósofos
    for (int i = 0; i < NUM_FILOSOFOS; i++)
    {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    // Esperar a que los hilos terminen (opcional)
    for (int i = 0; i < NUM_FILOSOFOS; i++)
    {
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}