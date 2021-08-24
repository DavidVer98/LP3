#include <stdio.h>
#include <assert.h>

int main()
{
    int x, y, z;
    x = 5;
    y = 5;
    z = x * y;
    assert(z == 24); // Assert se encarga que una condición se cumpla
                     // si la condición no se cumple el programa funcionara mal o termina
    printf("El valor de z es %d\n", x);
}