
#include <stdio.h>
#include "lectura_archivo.h"

int lectura_archivo (coord_puntos x[])
{
    FILE *file_points = fopen("Archivos/puntos.txt", "r");
    if (!file_points)
    {
        printf("ERROR al abrir el archivo\n\n");
        return 1;
    }
    for (int i = 0; i < CANT_PUNTOS; i++)
    {
        if (fscanf(file_points, "%f %f", &x[i].coord_x, &x[i].coord_y) != READ)
        {
            printf("Error al leer los valores del archivo\n\n");
            return 1;
        }
    }
    fclose(file_points);
}
