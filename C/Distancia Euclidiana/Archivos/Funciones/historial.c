
#include <stdio.h>
#include <time.h>
#include "historial.h"
#include "bubble_sort.h"
#include "promedio.h"

int historial (coord_puntos x[], float*y)
{
    time_t tiempo_actual = time(NULL);
    struct tm *fecha_hora = localtime(&tiempo_actual);
    FILE *history = fopen("Archivos/Historial.txt", "a");
    if (!history)
    {
        printf("ERROR al abrir el archivo\n\n");
        return 1;
    }
    fprintf(history, "%02d/%02d/%04d %02d:%02d:%02d\n\n",
            fecha_hora->tm_mday, fecha_hora->tm_mon + 1, fecha_hora->tm_year + 1900,
            fecha_hora->tm_hour, fecha_hora->tm_min, fecha_hora->tm_sec);

    fprintf(history, "Puntos utilizados: {(%.3f; %.3f); (%.3f; %.3f); (%.3f; %.3f)}\n\n", x[0].coord_x, x[0].coord_y, x[1].coord_x, x[1].coord_y, x[2].coord_x, x[2].coord_y);
    fputs("Distancias Euclidianas:\n", history);
    fprintf(history, "\t- 1er par de puntos --> {%.3f, %.3f} y {%.3f, %.3f} = %f\n", x[0].coord_x, x[0].coord_y, x[1].coord_x, x[1].coord_y, y[0]);
    fprintf(history, "\t- 2do par de puntos --> {%.3f, %.3f} y {%.3f, %.3f} = %f\n", x[1].coord_x, x[1].coord_y, x[2].coord_x, x[2].coord_y, y[1]);
    fprintf(history, "\t- 3er par de puntos --> {%.3f, %.3f} y {%.3f, %.3f} = %f\n\n", x[0].coord_x, x[0].coord_y, x[2].coord_x, x[2].coord_y, y[2]);
    bubble_sort(y);
    fprintf (history, "Menor Distancia Euclidiana --> %f\n", y[MENOR_SORT]);
    fprintf (history, "Menor Distancia Euclidiana --> %f\n", y[MAYOR_SORT]);
    fprintf(history, "Promedio de las Distancias Euclidianas --> %f\n", promedio(y));
    fputs("-----------------------------------------------------------------------------\n", history);
}
