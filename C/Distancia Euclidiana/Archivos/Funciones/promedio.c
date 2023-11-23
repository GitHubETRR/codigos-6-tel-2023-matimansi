
#include <stdio.h>
#include "promedio.h"

float promedio (float *x)
{
    float promedio = 0;
    for (int i = 0; i < CANT_PUNTOS; i++) promedio += x[i]; 
    promedio /= CANT_PUNTOS;
    printf("Promedio de las Distancias Euclidianas = %f\n\n", promedio);
    return (promedio);
}
