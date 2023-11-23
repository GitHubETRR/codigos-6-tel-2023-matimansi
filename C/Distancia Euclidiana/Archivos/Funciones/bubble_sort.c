
#include <stdio.h>
#include "bubble_sort.h"

void bubble_sort (float *x) 
{
    for (int i = 0; i < CANT_PUNTOS - 1; i++)
    {
        for (int j = 0; j < CANT_PUNTOS - i - 1; j++)
        {
            if (x[j] > x[j + 1])
            {
                float temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;
            }
        }
    }
    printf("Menor Distancia Euclidiana = %f\n", x[MENOR_SORT]);
    printf("Mayor Distancia Euclidiana = %f\n", x[MAYOR_SORT]);
}