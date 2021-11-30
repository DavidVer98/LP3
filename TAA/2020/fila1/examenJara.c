#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *llamada();

int main(void)
{
    int k;
    int n = 100; //definir tamaño maximo de hilos concurrentes
    pthread_t *hilo;

    hilo = malloc(n * sizeof(pthread_t));
    char buf[1024] = "1000";

    while (1 && k <= n)
    {
        k++;
        printf("Ingrese un nuevo comando a ejecutar\n");
        printf("$>");
        fgets(buf, 1024, stdin);
        printf("Ejecutando comando ingresado\n");
        pthread_create(&hilo[k], NULL, llamada, buf);

        //pseudocodigo**
        //agregar mas hilos si es que el valor de k=n
        //utilizando realloc y luego
        //aumentar el tamaño de n multiplicando por 2
    }

    return 0;
}

void *llamada(char *buf)
{
    system(buf);
    return 0;
}