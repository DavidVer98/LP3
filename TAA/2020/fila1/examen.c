#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

char buf[1024];
pthread_mutex_t mutex;


void* computer()
{
    pthread_mutex_lock(&mutex);
    printf("Ingrese un nuevo comando a ejecutar\n");
    printf("$>");
    fgets(buf, 1024, stdin);
    printf("Ejecutando comando ingresado\n");
    system(buf);
    pthread_mutex_unlock(&mutex);
}

int main(void)
{
    // char buf[1024];
    //int i = 0;
 while(1){
    pthread_t hilo;
    // hilo = malloc(sizeof(pthread_t));
    pthread_create(&hilo, NULL, &computer, NULL);

    pthread_join(hilo,NULL);
 }
    return 0;
}

