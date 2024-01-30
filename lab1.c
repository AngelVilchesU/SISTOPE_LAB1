#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "padre.h"


int main(int argc, char *argv[])
{

    /************************************ Lógica de solución - punto 1 ************************************/
    char *nombreArchivoEntrada, *nombreArchivoSalida, *anioInicioJuego, *precioMinimoJuego;
    int iFlag = 0, oFlag = 0, dFlag = 0, pFlag = 0, bFlag = 0, cantHijosCrear;
    int opt, err;
    printf("a");
    while ((opt = getopt(argc, argv, "i:o:d:p:b")) != -1)
    {
        switch (opt)
        {
        case 'i':
            iFlag = 1;
            nombreArchivoEntrada = optarg;
            break;
        case 'o':
            oFlag = 1;
            nombreArchivoSalida = optarg;
            break;
        case 'd':
            dFlag = 1;
            anioInicioJuego = optarg;
            break;
        case 'p':
            pFlag = 1;
            precioMinimoJuego = optarg;
            break;
        case 'b':
            bFlag = 1;
            break;
        case '?':    /* Caso no soportado */
            err = 1; /* Figura con error - err */
            break;
        }
    }
    /* Validación de la recepción de argumentos */
    if (iFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -i flag parameter\n", argv[0]);
        exit(1);
    }
    if (oFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -o flag parameter\n", argv[0]);
        exit(1);
    }
    if (dFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -d flag parameter\n", argv[0]);
        exit(1);
    }
    if (pFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -p flag parameter\n", argv[0]);
        exit(1);
    }
    /* Impresión de argumentos por pantalla */
    // printf("%s - %s - %s - %s - %d\n", nombreArchivoEntrada, nombreArchivoSalida, anioInicioJuego, precioMinimoJuego, bFlag);

    /************************************ Lógica de solución - punto 2 ************************************/
    cantHijosCrear = aniosDocumento(nombreArchivoEntrada);
    //printf("%d\n", cantHijosCrear);
    

    /************************************ Lógica de solución - punto 3 ************************************/
    
    archivoIntermedioOrd(nombreArchivoEntrada, cantHijosCrear, nombreArchivoSalida);

    /************************************ Lógica de solución - punto 4 ************************************/
    

    return 0;
}