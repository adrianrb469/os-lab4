#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESOS 5
#define NUM_RECURSOS 3

int main()
{
    int reclamados[NUM_PROCESOS][NUM_RECURSOS] = {
        {3, 2, 2},
        {6, 1, 3},
        {3, 1, 4},
        {4, 2, 2},
        {1, 2, 4}};

    int asignados[NUM_PROCESOS][NUM_RECURSOS] = {
        {1, 0, 0},
        {6, 1, 2},
        {2, 1, 1},
        {0, 0, 2},
        {1, 1, 1}};

    int disponibles[NUM_RECURSOS] = {9, 3, 6};

    bool terminar[NUM_PROCESOS] = {false};

    int contador = 0;
    while (contador < NUM_PROCESOS)
    {
        bool encontrado = false;
        for (int i = 0; i < NUM_PROCESOS; i++)
        {
            if (!terminar[i])
            {
                bool puede_terminar = true;
                for (int j = 0; j < NUM_RECURSOS; j++)
                {
                    if (reclamados[i][j] - asignados[i][j] > disponibles[j])
                    {
                        puede_terminar = false;
                        break;
                    }
                }

                if (puede_terminar)
                {
                    for (int j = 0; j < NUM_RECURSOS; j++)
                    {
                        disponibles[j] += asignados[i][j];
                    }
                    terminar[i] = true;
                    encontrado = true;
                    contador++;
                }
            }
        }

        if (!encontrado)
        {
            printf("El sistema está en un estado inseguro. Puede ocurrir un deadlock.\n");
            return 1;
        }
    }

    printf("El sistema está en un estado seguro. No habrá deadlock.\n");
    return 0;
}