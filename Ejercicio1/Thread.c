//gcc Thread.c -o fichero -pthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// devuelve un void puntero (recive un void puntero *data)
void *procesoSeparado(void *data){
    char *texto = (char *)data;
    while (1)
    {
        printf("%s\n",texto);
    }
    
}

int main(void){
   
   pthread_t proceso1;
   pthread_t proceso2;
   //creamos el proceso(&direccion de memoria,NULL,funcion que quermos ejecutar,&direccion de memoria del proceso separado, el argumento)
   pthread_create(&proceso1,NULL,&procesoSeparado,"hola");
   pthread_create(&proceso2,NULL,&procesoSeparado,"Adios");
   //Unimos los hilos de ejecuion al programa principal
   pthread_join(proceso1,NULL);
   pthread_join(proceso2,NULL);

    return 0;
}