
#include <stdio.h>
#include "impresion_puntos.h"

void impresion_puntos (coord_puntos x[])
{
    printf("Puntos = {");
    for (int i = 0; i < CANT_PUNTOS; i++)
    {
        printf("(%.3f, %.3f)", x[i].coord_x, x[i].coord_y);
        if (i < CANT_PUNTOS - 1) printf("; ");
    }
    printf("}\n\n");
    printf("1er par de puntos --> {%.3f, %.3f} y {%.3f, %.3f}\n", x[0].coord_x, x[0].coord_y, x[1].coord_x, x[1].coord_y);
    printf("2do par de puntos --> {%.3f, %.3f} y {%.3f, %.3f}\n", x[1].coord_x, x[1].coord_y, x[2].coord_x, x[2].coord_y);
    printf("3er par de puntos --> {%.3f, %.3f} y {%.3f, %.3f}\n\n", x[0].coord_x, x[0].coord_y, x[2].coord_x, x[2].coord_y);
}
