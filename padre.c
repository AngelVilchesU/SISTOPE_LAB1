#include "padre.h"
#include "tda_lista.h"



char *copiarString(char string[])
{
    char *str;
    str = (char *)malloc(300);
    strcpy(str, string);
    return (char *)str;
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
    int p1[2];

    if (pipe(p1) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }


    printf("Proceso con PID = %d, comienza\n", getpid());

    for (iter = 0; iter < aniosDocumento; iter++)
    {
        pid = fork(); // Crea un proceso hijo
        
    }
    if (pid > 0)  // Si es el padre
            printf("Soy el padre\n");
        else if (pid == 0) // Si es el hijo
        {
            printf("Soy el hijo\n");
        }
        else // Error
        {
            printf("ERROR\n");
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
void archivoIntermedioOrd(char *nombreDocumento, int cantAnios)
{
    FILE *dcto = fopen(nombreDocumento, "r"); // Se abre el archivo en modo lectura
    if (dcto == NULL)                         // En caso de que no se logre abrir
    {
        printf("%s: error in input file named\n", nombreDocumento);
        exit(-1);
    }
    int iter = 0, iter1 = 0, posicionAnio = 5, anio, ordenado, iter2, aux;
    int maxAnios[cantAnios]; // Arreglo con la cantidad de años a considerar
    char linea[300], *trozo, *auxStr, *nombreDocumentoInt;
    for (iter = 0; iter < cantAnios; iter++) // A continuación, el arreglo se rellena con ceros
    {
        maxAnios[iter] = 0;
    }
    while (fgets(linea, 300, dcto)) // Se lee el documento línea por línea
    {
        /* int,string,int,float,string,int,string,string,string,string */
        // printf("%s\n", linea);
        iter = 1;
        trozo = strtok(linea, ","); // Se particiona dicha línea de acuerdo a las comas (,)
        while (trozo != NULL)
        {
            // printf("%s\n", trozo);
            trozo = strtok(NULL, ","); // Extraemos trozo a trozo de lo particionado anteriormente
            if (iter == posicionAnio)  // Si el trozo extraído corresponde al año que queremos evaluar...
            {
                // printf("%s\n", trozo);
                anio = atoi(trozo); // Se convierte el año desde String a Entero
                iter1 = 0;
                while (iter1 < cantAnios) // Mientras el iterador sea menor al tamaño del arreglo
                {
                    if (maxAnios[iter1] == anio) // Si el arreglo en la posición especifica es igual al año considerado (existe)
                    {
                        iter1 = iter1 + cantAnios; // Finaliza el ciclo
                    }
                    else if (maxAnios[iter1] == 0) // Caso contrario, si el arreglo es 0 (no existe)
                    {
                        maxAnios[iter1] = anio;    // Se adiciona
                        iter1 = iter1 + cantAnios; // Finaliza el ciclo
                    }
                    iter1 = iter1 + 1; // Se continua el ciclo
                }
            }
            iter = iter + 1;
        }
    }
    /* Algoritmo de ordenamiento burbuja para el arreglo maxAnios */
    ordenado = 0;
    iter2 = 0;
    while (ordenado == 0)
    {
        ordenado = 1;
        for (int j = 0; j < cantAnios - iter2; j++)
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
    FILE *dctoInt = fopen("archivo_intermedio.csv", "a+");
    if (dctoInt == NULL)
    {
        printf("intermediate file creation error\n");
        exit(-1);
    }
    else
    {
        for (int i = 0; i < cantAnios; i++) // Para i menor que el tamaño del arreglo
        {
            // printf("%d|||%d\n", maxAnios[i], i);
            while (fgets(linea, 300, dcto)) // Mientras no se lean todas las líneas del archivo
            {
                /* int,string,int,float,string,int,string,string,string,string */
                // printf("Linea original: %s\n", linea);
                auxStr = copiarString(linea); // Se genera un auxiliar de la línea
                // printf("Linea copiada: %s\n", auxStr);
                iter = 1;                   // iterador para ................
                trozo = strtok(linea, ","); // Se particiona la línea extraida de acuerdo a las comas (,)
                while (trozo != NULL)       // Mientras no se tengo un trozo nulo
                {
                    // printf("%s\n", trozo);
                    trozo = strtok(NULL, ","); // Se particiona con la finalidad de obtener el año a evaluar
                    if (iter == posicionAnio)  // Si el iterador es igual a la posición en la que se encuetra el año a evualuar...
                    {
                        // printf("Anio: %s\n", trozo);
                        anio = atoi(trozo);      // Convierte el año a entero
                        if (maxAnios[i] == anio) // Si el año a evaluar es equivalente al año en el arreglo...
                        {
                            // printf("Contenido a copiar: %s\n", auxStr);
                            fprintf(dctoInt, "%s", auxStr); // Se escribe en el archivo intermedio
                        }
                    }
                    iter++;
                }
            }
            rewind(dcto);
        }
    }

    int anteriorSalto;
    for (int i = 0; i < cantAnios; i++)
    {
        TDAlista *lista = crearListaVacia();
        rewind(dctoInt);
        while (fgets(linea, 300, dctoInt) != NULL)
        {
            iter = 1;                   // iterador para ................
            auxStr = copiarString(linea); // Se genera un auxiliar de la línea
            trozo = strtok(linea, ","); // Se particiona la línea extraida de acuerdo a las comas (,)
            while (trozo != NULL)       // Mientras no se tengo un trozo nulo
            {
                trozo = strtok(NULL, ","); // Se particiona con la finalidad de obtener el año a evaluar
                if (iter == posicionAnio)  // Si el iterador es igual a la posición en la que se encuetra el año a evualuar...
                {
                    anio = atoi(trozo);      // Convierte el año a entero
                    if (maxAnios[i] == anio) // Si el año a evaluar es equivalente al año en el arreglo...
                    {
                        if (strstr(auxStr, trozo) != 0)
                        {
                            insertarInicio(lista, anteriorSalto);
                        }
                        anteriorSalto = ftell(dctoInt);
                    }
                }
                iter++;
            }
        }
        /* Pasar lista al hijo */





        

        liberarLista(lista);
    }

    fflush(dcto);
    fclose(dcto);
    fflush(dctoInt);
    fclose(dctoInt);
}