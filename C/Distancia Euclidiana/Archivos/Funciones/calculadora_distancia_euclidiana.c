
#include <stdio.h>
#include <math.h>
#include "calculadora_distancia_euclidiana.h"

void calculadora_distancia_euclidiana (float *x, coord_puntos y[])
{
    printf("Distancia Euclidiana:\n\n");
    x[0] = sqrt(pow((y[0].coord_x - y[1].coord_x), 2) + pow((y[0].coord_y - y[1].coord_y), 2));
    x[1] = sqrt(pow((y[1].coord_x - y[2].coord_x), 2) + pow((y[1].coord_y - y[2].coord_y), 2));
    x[2] = sqrt(pow((y[0].coord_x - y[2].coord_x), 2) + pow((y[0].coord_y - y[2].coord_y), 2));
}