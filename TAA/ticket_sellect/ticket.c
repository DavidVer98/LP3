#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // libreria para sleep

pthread_t *threads;

int n_vendedores;
int time_max;
int n_tickets;
int hilos_ventas[100];

pthread_mutex_t ventas_info_mutex = PTHREAD_MUTEX_INITIALIZER;

void kill_all_threads()
{

    for (int i = 0; i < n_vendedores; i++)
    {
        // We cancel all threads except to the current thread.
        if (pthread_self() != threads[i])
        {
            pthread_cancel(threads[i]);
        }
    }
    // Call the exit function so the main function can continue
    pthread_exit(NULL);
}

void *simulador_ventas(void *parametros)
{
    int seller = *((int *)(parametros));
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    int random = rand() % (time_max) + 1;
    sleep(random);

    pthread_mutex_lock(&ventas_info_mutex);
    printf("Seller #%d ", seller);

    n_tickets--;
    hilos_ventas[seller] += 1;
    printf("sold one (%d left) \n", n_tickets);
    if (n_tickets == 0)
    {
        kill_all_threads();
    }

    pthread_mutex_unlock(&ventas_info_mutex);
}

int main(int *arg, const char *argv[])
{

    n_vendedores = atoi(argv[1]);
    time_max = atoi(argv[2]);
    n_tickets = atoi(argv[3]);


    threads = (pthread_t *)malloc(n_vendedores * sizeof(pthread_t));
    int *numero_agentes = (int *)malloc(n_vendedores * sizeof(int));

    while (n_tickets != 0)
    {
        for (int i = 0; i < n_vendedores; i++)
        {
            if(n_tickets >= 0)
            {
            numero_agentes[i] = i;
            pthread_create((threads + i), NULL, &simulador_ventas, &numero_agentes[i]);
            }
        }
        for (int i = 0; i < n_vendedores; i++)
        {
            if(n_tickets >= 0){
            pthread_join(threads[i], NULL);
            }
        }
    }
      for (int i = 0; i < n_vendedores; i++)
      {
          printf("Seller #%d noticed all tickets sold! (I sold %d myself)\n",i,hilos_ventas[i]);
      }

    printf("All done!\n");
    return 0;
}