#include "padre.h"

// Entradas: Se recibe una cadena de caracteres
// Salida: Se retorna un puntero a la cadena de caracteres a copiar
// Descripción: Mediante el uso de una variable char* con un adecuado manejo de memoria
//              se emplea la función strcpy la cual permite, con el uso de un destino
//              y valor, copiar la información en su interior (char*) retornando un puntero
//              hacia dicha información
char *copiarString(char string[])
{
    char *str;
    str = (char *)malloc(300);
    strcpy(str, string);
    return (char *)str;
}

// Entradas: Se recibe una lista enlazada con las diferentes posiciones a evaluar por este hijo especifico
// Salidas: void
// Descripción: De acuerdo a la lista enlazada con las diferentes posiciones a evaluar
//              se crea un hijo mediante fork al cual se le asignará el cálculo asociado a la
//              obtención de valores (juego más caro, barato, gratis, promedio de precios y
//              porcentaje de plataformas disponibilizadas) para finalmente terminar su
//              ejecución             
void crearHijos(TDAlista* lista)
{
    pid_t pid;
    int iter, num;
    pid = fork(); // Crea un proceso hijo
    if (pid == 0) // Si es el hijo
    {
        wait(NULL);
        calculos(lista); // Se llama a la función calculos la cual realizará todos los cálculos asociados a este hijo (, nombrearchivo)
        exit(wait(NULL));
    }
    else if (pid == -1) // Error
    {

        printf("ERROR\n");
    }
}

// Entrada: Se recibe el nombre del archivo/documento de entrada
// Salida: Se retorna el número de años de dicho documento (fecha de lanzamiento) sin repetición
// Descripción: Se abre el archivo con flag de lectura para luego, una vez inicializado un arreglo de enteros,
//              leer línea por línea extrayendo el año de lanzamiento de cada juego en el documento ingresandoles
//              sin repetición en el arreglo aludido determinando así con una variable iterativa (cantidadAnios)
//              el número de años sin repetición presentes en el documento
int aniosDocumento(char *nombreDocumento)
{
    FILE *dcto = fopen(nombreDocumento, "r"); // Se abre el documento con flag de lectura
    if (dcto == NULL) // En caso de algún error asociado
    {
        printf("%s: error in input file named\n", nombreDocumento);
        exit(-1);
    }
    int cantidadAnios = 0, iter = 0, iter1 = 0, arrTamanio = 60, posicionAnio = 5, anio; /* catidadAnios: refiere a la cantidad de años del documento (distintos) */
    // Se inicializa un arreglo estático cuyo propósito es almacenar los años de los juegos
    // sin repetición, su valor es 60 ya que los juegos (videojuegos) no se han creado desde
    // una fecha anterior a esta (en años)
    int maxAnios[arrTamanio];
    char linea[300], *trozo;
    for (iter = 0; iter < arrTamanio; iter++) // Arreglo inicializado en 0
    {
        maxAnios[iter] = 0;
    }
    while (fgets(linea, 300, dcto)) // Mientras no se lea cada línea en el documento de entrada
    {
        iter = 1; // Iterador para avanzar en el buffer del a continuación strtok
        trozo = strtok(linea, ","); // Particionamiento de la línea del archivo de entrada (",")
        while (trozo != NULL) // Mientras los trozos apuntados no figuren como un nulo
        {
            trozo = strtok(NULL, ",");
            if (iter == posicionAnio) // Si el iterador coinicide con la posición del año en la línea
            {
                anio = atoi(trozo); // Se convierte el dato (año) desde string/char* a entero
                iter1 = 0; // iterador por concepto de rellenamiento de arreglo
                while (iter1 < arrTamanio) // Mientras el iterador sea menor al tamaño del arreglo contenedor de años
                {
                    if (maxAnios[iter1] == anio) // Si el arreglo en la posición actual contiene el año actual
                    {
                        iter1 = iter1 + arrTamanio; // Finaliza el ciclo (ya existe el año)
                    }
                    else if (maxAnios[iter1] == 0) // Si se llega a un valor 0, es decir, no se posee el año actual
                    {
                        maxAnios[iter1] = anio; // Se adiciona el año
                        cantidadAnios = cantidadAnios + 1; // Variable que considera la cantidad de años sin repetición
                        iter1 = iter1 + arrTamanio; // Finaliza el ciclo (se ha agregado el año)
                    }
                    iter1 = iter1 + 1;
                }
            }
            iter = iter + 1;
        }
    }
    fclose(dcto); // Se cierra el documento de entrada
    return cantidadAnios; // Se retorna la cantidad de años sin repetición
}

// Entrada: Se recibe el nombre del archivo/documento de entrada
// Salida: void
// Descripción: Se abre el archivo con flag de lectura para luego, una vez inicializado un arreglo de enteros,
//              leer línea por línea extrayendo el año de lanzamiento de cada juego en el documento ingresandoles
//              sin repetición en el arreglo aludido, una vez analizado el documento en su totalidad se aplica
//              sobre el arreglo el algoritmo de ordenamiento burbuja para ordenar su contenido (años) de forma
//              ascendente para luego crear un archivo intermedio al cual se le escribirá el contenido
//              del archivo de entrada en orden ascendente de acuerdo a los años empleando el arreglo anteriormente.
//              Posteriormente, se crea una lista enlazada por cada año sin repetición de modo que, extrayendo
//              gracias la función ftell la información asociada a la posición de cada línea en el archivo
//              de acuerdo al año evaluado en la iteración para posteriormente entregarle esta información a un
//              hijo en particular finalmente cerrando los archivos abiertos
void archivoIntermedioOrd(char *nombreDocumento, int cantAnios)
{
    FILE *dcto = fopen(nombreDocumento, "r"); // Se abre el archivo en modo lectura
    if (dcto == NULL) // En caso de que no se logre abrir
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
        iter = 1;
        trozo = strtok(linea, ","); // Se particiona dicha línea de acuerdo a las comas (,)
        while (trozo != NULL)
        {
            trozo = strtok(NULL, ","); // Extraemos trozo a trozo de lo particionado anteriormente
            if (iter == posicionAnio)  // Si el trozo extraído corresponde al año que queremos evaluar...
            {
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
    /* Algoritmo de ordenamiento burbuja para el arreglo maxAnios (se ordenan los años) */
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
    rewind(dcto); // Se reinicia el apuntador del archivo (al principio)
    FILE *dctoInt = fopen("archivo_intermedio.csv", "a+"); // Se abre el archivo intermedio con flag de adición y lectura
    if (dctoInt == NULL) // En caso de un error asociado
    {
        printf("intermediate file creation error\n");
        exit(-1);
    }
    else
    {
        for (int i = 0; i < cantAnios; i++) // Para i menor que el tamaño del arreglo
        {
            while (fgets(linea, 300, dcto)) // Mientras no se lean todas las líneas del archivo
            {
                auxStr = copiarString(linea); // Se genera un auxiliar de la línea
                iter = 1;                   // iterador para conseguir la información asociada l
                trozo = strtok(linea, ","); // Se particiona la línea extraida de acuerdo a las comas (,)
                while (trozo != NULL)       // Mientras no se tengo un trozo nulo
                {
                    trozo = strtok(NULL, ","); // Se particiona con la finalidad de obtener el año a evaluar
                    if (iter == posicionAnio)  // Si el iterador es igual a la posición en la que se encuetra el año a evualuar...
                    {
                        anio = atoi(trozo);      // Convierte el año a entero
                        if (maxAnios[i] == anio) // Si el año a evaluar es equivalente al año en el arreglo...
                        {
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
    for (int i = 0; i < cantAnios; i++) // Mientras i sea menor a la cantidad de años totales
    {
        TDAlista *lista = crearListaVacia(); // Se crea una lista enlazada
        rewind(dctoInt);
        while (fgets(linea, 300, dctoInt) != NULL) // Se evalua el documento intermedio línea por línea
        {
            iter = 1;                     // iterador para conseguir la información asociada a la posición del año
            auxStr = copiarString(linea); // Se genera un auxiliar de la línea
            trozo = strtok(linea, ",");   // Se particiona la línea extraida de acuerdo a las comas (,)
            while (trozo != NULL)         // Mientras no se tengo un trozo nulo
            {
                trozo = strtok(NULL, ","); // Se particiona con la finalidad de obtener el año a evaluar
                if (iter == posicionAnio)  // Si el iterador es igual a la posición en la que se encuetra el año a evualuar...
                {
                    anio = atoi(trozo);      // Convierte el año a entero
                    if (maxAnios[i] == anio) // Si el año a evaluar es equivalente al año en el arreglo...
                    {
                        if (strstr(auxStr, trozo) != 0)
                        {
                            insertarInicio(lista, anteriorSalto); // Se inserta la información asociada a la posición de la línea en el archivo
                        }
                        anteriorSalto = ftell(dctoInt);
                    }
                }
                iter++;
            }
        }
        // La información asociada a las posiciones a evaluar por los hijos se encuentra
        // anexada a la lista enlazada y a continuación es entregada a cada hijo, de forma
        // especifica y particula
        crearHijos(lista);
        liberarLista(lista);
    }
    fflush(dcto);
    fclose(dcto);
    fflush(dctoInt);
    fclose(dctoInt);
}