// Hilos:Threads
// Funciones utilizadas:
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                     void *(*start_routine) (void*), void *arg);
// int pthread_join(pthread_t thread, void **retval);

// Ejemplo: Crear un hilo que escriba x líneas en un archivo de texto


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void *thread_routine(void *arg)
{   
    int nr_lineas = *((int *) arg);
    int fd;
    char buf[] = "Nueva linea..\n";

    printf("El hilo comienza a ejecutarse...\n");
    for (int i=0; i<nr_lineas; i++)
    {
        fd = open("/home/david/Escritorio/gitlp3/LP3/Practica/C/Thread/hilos/file.txt",O_WRONLY|O_APPEND);
        write(fd,buf,sizeof(buf)-1);
        close(fd);

    }
}

int main(int argc, char *argv[])
{
    // declarar una variable de tipo pthread_t
    // thread1 es el identificador del hilo
    pthread_t thread1;
    int value = atoi(argv[1]);
    if (0 != pthread_create(&thread1,NULL,thread_routine,&value))
        return -1;
    // Esperara hasta que el hilo finalice
    pthread_join(thread1, NULL);

    return 0;
}