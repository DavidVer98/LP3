#include <stdio.h>
#include<stdio.h> 
#include<pthread.h>
#include <stdlib.h>
int step_i = 0;


#define FILAS_MATRIZ_A 3
#define COLUMNAS_MATRIZ_A 3
#define FILAS_MATRIZ_B 3
#define COLUMNAS_MATRIZ_B 2


void* multi(void* arg);
#define MAX_THREAD 3
pthread_mutex_t muteo;
int matrizA[FILAS_MATRIZ_A][COLUMNAS_MATRIZ_A] = {
{3, 2, 1},
{1, 1, 3},
{0, 2, 1}
};
int matrizB[FILAS_MATRIZ_B][COLUMNAS_MATRIZ_B] = {
{2, 1},
{1, 0},
{3, 2}
};
int producto[FILAS_MATRIZ_B][COLUMNAS_MATRIZ_B];

void* multi(void* arg) {
  
  int i = (int*) arg; //posicion de la fila a calcular
 
  for (int j = 0; j < COLUMNAS_MATRIZ_B; j++) {
      for (int k = 0; k < COLUMNAS_MATRIZ_A; k++) {
          producto[i][j] += matrizA[i][k] *matrizB[k][j];
        }
    }
  return 0;
}
int main(void) {

   pthread_t *tid;
  tid = malloc(MAX_THREAD*sizeof(pthread_t));
  pthread_mutex_init (&muteo, NULL);

    // Se crean 3 hilos, cada uno calcula 1 fila del resultado
  
  for (int i = 0; i < MAX_THREAD; i++) {
     
        pthread_create(tid+i, NULL, multi,(void*)(i));
  }

  for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(tid[i], NULL);
    }
  printf("Imprimiendo producto\n");
  for (int i = 0; i < FILAS_MATRIZ_B; i++) 
  {
     for (int j = 0; j < COLUMNAS_MATRIZ_B; j++) {
       printf("%d ", producto[i][j]);
    }
    printf("\n");
  }
}