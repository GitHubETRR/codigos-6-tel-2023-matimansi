
#include <stdio.h>

#include "Archivos/Definiciones/definciones.h"
#include "Archivos/Funciones/program_message.h"
#include "Archivos/Funciones/lectura_archivo.h"
#include "Archivos/Funciones/impresion_puntos.h"
#include "Archivos/Funciones/calculadora_distancia_euclidiana.h"
#include "Archivos/Funciones/historial.h"
#include "Archivos/Funciones/bubble_sort.h"
#include "Archivos/Funciones/promedio.h"

int main()
{
    float distancia_euclidiana[CANT_PUNTOS] = {0};
    float *puntero_distancia_euclidiana = &distancia_euclidiana[0];
    coord_puntos punto[3];

    program_message();

    if (lectura_archivo(punto)) return 1;

    impresion_puntos(punto);

    calculadora_distancia_euclidiana(puntero_distancia_euclidiana, punto);

    historial(punto, puntero_distancia_euclidiana);

    printf("Presione cualquier tecla para cerrar el programa y actualizar el historial...");
    getchar();

    return 0;
}
