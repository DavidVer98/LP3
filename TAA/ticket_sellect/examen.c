//tema 2 ejercicio
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAX_THREAD 2
#define MIN 0.1
#define MAX 0.35

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t semaforo;

int tickets = 11;

struct args
{
    int hilo, ticketsVendidos;
    int *index;
};

void *vender(void *arg)
{

    struct args *p = (struct args *)arg;

    while (tickets > 0)
    {
        // pthread_mutex_lock(&mutex);
        sem_wait(&semaforo);
        printf("Seller %d\n", p->hilo);
        tickets--;
        printf("Seller #%d sold one (%d left)\n", p->hilo, tickets);
        // pthread_mutex_unlock(&mutex);
        sem_post(&semaforo);
        p->ticketsVendidos = p->ticketsVendidos + 1;
        sleep(5);
    }

    //pthread_mutex_unlock(&mutex);
}

int main(void)
{
    sem_init(&semaforo, 0, 1);

    int i;
    struct args arg[MAX_THREAD];

    //Creamos un vector de hilos
    pthread_t threads[MAX_THREAD];

    // Creacion de hilos
    for (int i = 0; i < MAX_THREAD; i++)
    {
        arg[i].hilo = i;

        arg[i].ticketsVendidos = 0;

        pthread_create(&threads[i], NULL, &vender, &arg[i]);
    }

    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < MAX_THREAD; i++)
    {
        printf("el hilo %d  vendio %d tickets\n", i, arg[i].ticketsVendidos);
    }

    sem_destroy(&semaforo);
    return 0;
}
