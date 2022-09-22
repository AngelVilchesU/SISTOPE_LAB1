#include "padre.h"

/* Proceso sin implementar - temporal */
int procesoHijoID(){
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
        if (pid > 0) // Si es el padre
            continue;
        else if (pid == 0) // Si es el hijo
        {
            exit(proceso());
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
    while (1)
    {
        sleep(30);
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
        printf("%s: error in input file named", nombreDocumento);
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