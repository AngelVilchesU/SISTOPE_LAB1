#include "padre.h"

/* Proceso sin implementar - temporal */
int procesoHijoID()
{
    printf("HIJO de PID = %d\n", getpid());
    return 0;
}

// Entradas: Se recibe el número de años del documento/archivo de entrada (sin repetición)
// Salidas: Se retorna el valor entero positivo 1 señalando la correcta creación de hijos
// Descripción: Se realiza un ciclo el cual crea procesos hijos equivalentes al número ingresado
//              inicialmente como parametro de entrada
int crearHijos(int aniosDocumento)
{
    pid_t pid;
    int iter;
    int status;
    printf("Proceso con PID = %d, comienza\n", getpid());

    for (iter = 0; iter < aniosDocumento; iter++)
    {
        pid = fork(); // Crea un proceso hijo
        if (pid > 0)  // Si es el padre
            continue;
        else if (pid == 0) // Si es el hijo
        {
            exit(procesoHijoID());
        }
        else // Error
        {
            printf("ERROR\n");
        }
    }
    for (int i = 0; i < aniosDocumento; i++)
    {
        pid = wait(&status);
        printf("PADRE de PID = %d con HIJO de PID = %d finalizado\n", getpid(), pid);
    }
    return 1;
}

// Entrada: Se recibe el nombre del archivo/documento de entrada
// Salida: Se retorna el número de años de dicho documento (fecha de lanzamiento) sin repetición
// Descripción: Se abre el archivo con flag de lectura para luego, una vez inicializado un arreglo de enteros,
//              leer línea por línea extrayendo el año de lanzamiento de cada juego en el documento ingresandoles
//              sin repetición en el arreglo aludido determinando así con una variable iterativa (cantidadAnios)
//              el número de años sin repetición presentes en el documento
int aniosDocumento(char *nombreDocumento)
{
    FILE *dcto = fopen(nombreDocumento, "r");
    if (dcto == NULL)
    {
        printf("%s: error in input file named\n", nombreDocumento);
        exit(-1);
    }
    int cantidadAnios = 0, iter = 0, iter1 = 0, arrTamanio = 60, posicionAnio = 5, anio; /* catidadAnios: refiere a la cantidad de años del documento (distintos) */
    int maxAnios[arrTamanio];
    char linea[300], *trozo;
    for (iter = 0; iter < arrTamanio; iter++)
    {
        maxAnios[iter] = 0;
    }
    while (fgets(linea, 300, dcto))
    {
        /* int,string,int,float,string,int,string,string,string,string */
        // printf("%s\n", linea);
        iter = 1;
        trozo = strtok(linea, ",");
        while (trozo != NULL)
        {
            // printf("%s\n", trozo);
            trozo = strtok(NULL, ",");
            if (iter == posicionAnio)
            {
                // printf("%s\n", trozo);
                anio = atoi(trozo);
                iter1 = 0;
                while (iter1 < arrTamanio)
                {
                    if (maxAnios[iter1] == anio)
                    {
                        iter1 = iter1 + arrTamanio;
                    }
                    else if (maxAnios[iter1] == 0)
                    {
                        maxAnios[iter1] = anio;
                        cantidadAnios = cantidadAnios + 1;
                        iter1 = iter1 + arrTamanio;
                    }
                    iter1 = iter1 + 1;
                }
            }
            iter = iter + 1;
        }
    }
    fclose(dcto);
    return cantidadAnios;
}

// Entrada: Se recibe el nombre del archivo/documento de entrada
// Salida: Se retorna el nombre de un archivo (intermedio) con el contenido del archivo de entrada ordenado
//         por los años de forma ascendente
// Descripción: Se abre el archivo con flag de lectura para luego, una vez inicializado un arreglo de enteros,
//              leer línea por línea extrayendo el año de lanzamiento de cada juego en el documento ingresandoles
//              sin repetición en el arreglo aludido, una vez analizado el documento en su totalidad se aplica
//              sobre el arreglo el algoritmo de ordenamiento burbuja para ordenar su contenido (años) de forma
//              ascendente para finalmente crear un archivo intermedio al cual se le escribirá el contenido
//              del archivo de entrada en orden ascendente de acuerdo a los años empleando el arreglo anteriormente
//              ordenado cerrando los archivos abiertos y retornando el nombre del archivo intermedio generado
char * archivoIntermedioOrd(char *nombreDocumento)
{
    FILE *dcto = fopen(nombreDocumento, "r");
    if (dcto == NULL)
    {
        printf("%s: error in input file named\n", nombreDocumento);
        exit(-1);
    }
    int iter = 0, iter1 = 0, arrTamanio = 60, posicionAnio = 5, anio, ordenado, iter2, aux;
    int maxAnios[arrTamanio];
    char linea[300], *trozo, *auxStr, *nombreDocumentoInt;
    strcpy(nombreDocumentoInt, "archivo_intermedio.csv");
    for (iter = 0; iter < arrTamanio; iter++)
    {
        maxAnios[iter] = 0;
    }
    while (fgets(linea, 300, dcto))
    {
        /* int,string,int,float,string,int,string,string,string,string */
        // printf("%s\n", linea);
        iter = 1;
        trozo = strtok(linea, ",");
        while (trozo != NULL)
        {
            // printf("%s\n", trozo);
            trozo = strtok(NULL, ",");
            if (iter == posicionAnio)
            {
                // printf("%s\n", trozo);
                anio = atoi(trozo);
                iter1 = 0;
                while (iter1 < arrTamanio)
                {
                    if (maxAnios[iter1] == anio)
                    {
                        iter1 = iter1 + arrTamanio;
                    }
                    else if (maxAnios[iter1] == 0)
                    {
                        maxAnios[iter1] = anio;
                        iter1 = iter1 + arrTamanio;
                    }
                    iter1 = iter1 + 1;
                }
            }
            iter = iter + 1;
        }
    }
    /* Algoritmo de ordenamiento burbuja */
    ordenado = 0;
    iter2 = 0;
    while (ordenado == 0)
    {
        ordenado = 1;
        for (int j = 0; j < arrTamanio - iter2; j++)
        {
            if (maxAnios[j] > maxAnios[j + 1])
            {
                aux = maxAnios[j];
                maxAnios[j] = maxAnios[j + 1];
                maxAnios[j + 1] = aux;
                ordenado = 0;
            }
        }
        iter2++;
    }
    rewind(dcto);
    FILE *dctoInt = fopen("archivo_intermedio.csv", "a");
    if (dctoInt == NULL)
    {
        printf("%s: intermediate file creation error\n", nombreDocumentoInt);
        exit(-1);
    }
    else
    {
        for (int i = 0; i <= arrTamanio; i++)
        {
            // printf("%d\n", maxAnios[i]);
            if (maxAnios[i] != 0)
            {
                while (fgets(linea, 300, dcto))
                {
                    /* int,string,int,float,string,int,string,string,string,string */
                    // printf("%s\n", linea);

                    strcpy(auxStr, linea);
                    iter = 1;
                    trozo = strtok(linea, ",");
                    while (trozo != NULL)
                    {
                        // printf("%s\n", trozo);
                        trozo = strtok(NULL, ",");
                        if (iter == posicionAnio)
                        {
                            // printf("%s\n", trozo);
                            anio = atoi(trozo);
                            if (maxAnios[i] == anio)
                            {
                                // printf("%s\n", auxStr);
                                fprintf(dctoInt, "%s", auxStr);
                            }
                        }
                        iter++;
                    }
                }
                rewind(dcto);
            }
        }
        
    }
    fclose(dcto);
    fflush(dctoInt);
    fclose(dctoInt);
    return nombreDocumentoInt;
}