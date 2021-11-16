#include <stdio.h>

int main(){
    //stdin --> para recibir entrada por teclado
    // FILE *archivo;
    // archivo  = stdout;
    // fprintf(archivo,"Hola archivo\n");
    //------------------------------------------
    // FILE *archivo;
    // int x;
    // archivo = stdin;
    // printf("Ingrese un numero :");
    // fscanf(archivo,"%d" ,&x);
    // printf("El valor es %d\n",x);
    //-------------Forma abreviada--------------

    int x;
    printf("Ingrese un numero :");
    scanf("%d",&x);
    printf("El valor es %d\n",x);
    return 0;   
}s