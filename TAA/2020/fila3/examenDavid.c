#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // libreria para sleep
// #include <limits.h>
#include <time.h>

// #include <signal.h>
int n_agentes, time_max, n_maxInfecciones;
int numero_contagiados;
pthread_t *threads_id;

pthread_mutex_t infection_info_mutex = PTHREAD_MUTEX_INITIALIZER;

void kill_all_threads()
{

    for (int i = 0; i < n_agentes; i++)
    {
        // We cancel all threads except to the current thread.
        if (pthread_self() != threads_id[i])
        {
            pthread_cancel(threads_id[i]);
        }
    }
    // Call the exit function so the main function can continue
    pthread_exit(NULL);
}

void *infectar(void *parametros)
{

    int agentes_n = *((int *)parametros);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    int random = rand() % (time_max )+1;
    sleep(random);
    pthread_mutex_lock(&infection_info_mutex);
    printf("Agente #%d ", agentes_n);
    printf("infecto a una persona luego de %ds.  ", random);
    numero_contagiados += 1;
    printf("( total contagiados %d)\n", numero_contagiados);
    if (numero_contagiados == n_maxInfecciones)
    {
        kill_all_threads();
    }

    pthread_mutex_unlock(&infection_info_mutex);
}

int main(int *args, char *const argv[])
{
    time_t begin, end;
    time(&begin);

    n_agentes = atoi(argv[1]);
    time_max = atoi(argv[2]);
    n_maxInfecciones = atoi(argv[3]);

    threads_id = (pthread_t *)malloc(n_agentes * sizeof(pthread_t));
    int *numero_agentes = (int *)malloc(n_agentes * sizeof(int));

    while (numero_contagiados < n_maxInfecciones)
    {
        for (int i = 0; i < n_agentes; i++)
        {
            if (numero_contagiados <= n_maxInfecciones)
            {
                numero_agentes[i] = i + 1;
                pthread_create((threads_id + i), NULL, &infectar, &numero_agentes[i]);
            }
        }
        // printf("\n-------------------\n");
        for (int i = 0; i < n_agentes; i++)
        {
            if (numero_contagiados <= n_maxInfecciones)
            {
                pthread_join(threads_id[i], NULL);
            }
        }

    }
        time(&end);
        time_t elapsed = end - begin;
        printf("Total de %d contagiados en %ld seconds.\n",n_maxInfecciones,elapsed);
    // printf("Numero de agentes %d\nTiempo maximo de entre infecciones %d\nEl numero maximo de infecciones %d\n",n_agentes,time_max,n_maxInfecciones);
}