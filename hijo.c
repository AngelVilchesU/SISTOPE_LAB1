#include "hijo.h"

// Entradas: Se recibe una cadena de caracteres
// Salida: Se retorna un puntero a la cadena de caracteres a copiar
// Descripción: Mediante el uso de una variable char* con un adecuado manejo de memoria
//              se emplea la función strcpy la cual permite, con el uso de un destino
//              y valor, copiar la información en su interior (char*) retornando un puntero
//              hacia dicha información
char *copiarStringHijo(char string[])
{
    char *str;
    str = (char *)malloc(300);
    strcpy(str, string);
    return (char *)str;
}

// Entradas: Se ingresa un arreglo de enteros contenedores de los valores de los cuales se calcula un promedio
// Salidas: Se retorna el promedio de los valores ingresados
// Descripción: Se realiza una suma de todos los valores en el arreglo de acuerdo a su longitud
//              para posteriormente retornar la suma dividada del número de valores contenidos
float promedio(int arr[], int largoArr)
{
    float sumaTotal = 0;
    for (int i = 0; i < largoArr; i++)
    {
        sumaTotal = sumaTotal + arr[i];
    }
    return sumaTotal / largoArr;
}

// Entradas: Se ingresa un valor total (100%) y un número (0% <= x% <= 100%)
// Salidas: Se retorna el porcentaje al cual se asocia el número ingresado respecto del total
// Descripción: El número ingresado se multiplica por 100 para luego retornar el resultado
//              de su divisón por el total ingresado
float porcentaje(int total, int nro)
{
    float porcentaje;
    porcentaje = (nro * 100) / total;
    return porcentaje;
}

// Entradas: Se ingresa una lista enlazada
// Salidas: 
// Descripción: 
char** calculos(TDAlista *lista)
{
    int cantNodos = nroNodosLista(lista);
    char str[cantNodos][300];
    for (int i = 0; i < cantNodos; i++)
    {
        int pos = retornarDato(lista);
        eliminarInicio(lista);
        char linea[300];

        FILE *dctoInt = fopen("archivo_intermedio.csv", "r");
        if (dctoInt == NULL)
        {
            printf("intermediate file read error\n");
            exit(-1);
        }
        else
        {
            fseek(dctoInt, pos, SEEK_SET);
            fgets(linea, 300, dctoInt);
            strcpy(str[i], linea);
        }
        fclose(dctoInt);
    }
    ////////////// Calculos ////////////////

    // Obtener el juego más caro, barato, promedio de precios del año, porcentaje de SO y gratuitos
    char *juegoMasCaro, *juegoMasBarato;
    int posicionPrecio = 3, iter, precioMax = 0, precioMin = 0, posicionGratis = 8, posicionW = 9, posicionM = 10, posicionL = 11;
    int nroJuegosW = 0, nroJuegosM = 0, nroJuegosL = 0, posicionAnio = 7;
    float porcentajeWs, porcentajeMc, porcentajeLx;
    int preciosAnio[cantNodos];
    float promPreciosAnio;
    int nroJuegosGratis = 0, anioEvaluado;
    char *trozo, *auxStr, *auxStr1, *trozoJuego, *comparador;
    char yes[4] = "Yes", esGratis[5] = "True";
    for (int i = 0; i < cantNodos; i++)
    {
        /* int,string,int,float,string,int,string,string,string,string */
        iter = 1;
        auxStr = copiarStringHijo(str[i]);
        trozo = strtok(auxStr, ",");
        while (trozo != NULL)
        {
            // printf("%s\n", trozo);
            trozo = strtok(NULL, ",");
            if (iter == posicionPrecio)
            {
                int precioAct = atoi(trozo);
                if (precioAct > precioMax)
                {
                    precioMax = precioAct;
                    auxStr1 = copiarStringHijo(str[i]);
                    trozoJuego = strtok(auxStr1, ",");
                    trozoJuego = strtok(NULL, ",");
                    juegoMasCaro = copiarStringHijo(trozoJuego);
                }
                if (i == 0) // Primera iteración
                {
                    precioMin = precioAct;
                    auxStr1 = copiarStringHijo(str[i]);
                    trozoJuego = strtok(auxStr1, ",");
                    trozoJuego = strtok(NULL, ",");
                    juegoMasBarato = copiarStringHijo(trozoJuego);
                }
                else if (precioAct < precioMin)
                {
                    precioMin = precioAct;
                    auxStr1 = copiarStringHijo(str[i]);
                    trozoJuego = strtok(auxStr1, ",");
                    trozoJuego = strtok(NULL, ",");
                    juegoMasBarato = copiarStringHijo(trozoJuego);
                }
                preciosAnio[i] = precioAct;
            }

            if (iter == posicionW)
            {
                comparador = copiarStringHijo(trozo);
                if (strcmp(yes, comparador) == 0)
                {
                    nroJuegosW++;
                }
            }
            if (iter == posicionM)
            {
                comparador = copiarStringHijo(trozo);
                if (strcmp(yes, comparador) == 0)
                {
                    nroJuegosM++;
                }
            }
            if (iter == posicionL)
            {
                comparador = copiarStringHijo(trozo);
                comparador = strtok(comparador, "\n");
                if (strcmp(yes, comparador) == 0)
                {
                    nroJuegosL++;
                }
            }
            if (iter == posicionGratis)
            {
                comparador = copiarStringHijo(trozo);
                if (strcmp(esGratis, comparador) == 0)
                {
                    nroJuegosGratis++;
                }
            }
            if (iter == posicionAnio)
            {
                anioEvaluado = atoi(trozo); // Se convierte el año desde String a Entero
            }
            iter = iter + 1;
        }
    }
    char *juegosGratis[nroJuegosGratis];
    //char arregloFinal[6][300];
    char **arregloFinal = (char**)malloc(sizeof(char*)*6);
    for (int i = 0; i < 6; i++)
    {
        arregloFinal[i] = (char*)malloc(sizeof(char)*300);
    }
    
    int contador = 0;
    posicionGratis = 6;
    promPreciosAnio = promedio(preciosAnio, cantNodos);
    porcentajeWs = porcentaje((nroJuegosW + nroJuegosM + nroJuegosL), nroJuegosW);
    porcentajeMc = porcentaje((nroJuegosW + nroJuegosM + nroJuegosL), nroJuegosM);
    porcentajeLx = porcentaje((nroJuegosW + nroJuegosM + nroJuegosL), nroJuegosL);
    for (int i = 0; i < cantNodos; i++)
    {
        /* int,string,int,float,string,int,string,string,string,string */
        iter = 1;
        auxStr = copiarStringHijo(str[i]);
        trozo = strtok(auxStr, ",");
        while (trozo != NULL)
        {
            // printf("%s\n", trozo);
            trozo = strtok(NULL, ",");
            if (iter == posicionGratis)
            {
                comparador = copiarStringHijo(trozo);
                if (strcmp(esGratis, comparador) == 0)
                {
                    auxStr1 = copiarStringHijo(str[i]);
                    trozoJuego = strtok(auxStr1, ",");
                    trozoJuego = strtok(NULL, ",");
                    juegosGratis[contador] = copiarStringHijo(trozoJuego);
                    contador++;
                }
            }
            iter = iter + 1;
        }
    }
    //aqui esta todo
    
    char linea1[300];
    char linea2[300];
    char linea3[300];
    char linea4[300];
    char linea5[300];
    char linea6[300];
    sprintf(arregloFinal[0],"Año %d\n",anioEvaluado);
    sprintf(arregloFinal[1],"Juego mas caro: %s\n", juegoMasCaro);
    sprintf(arregloFinal[2],"Juego mas barato: %s\n", juegoMasBarato);
    sprintf(arregloFinal[3],"Promedio de precios: %f\n", promPreciosAnio);
    sprintf(arregloFinal[4],"Windows: %f , Mac: %f , Linux: %f\n", porcentajeWs, porcentajeMc, porcentajeLx);
    sprintf(linea6,"Juegos gratis: \n");
    for (int i = 0; i < nroJuegosGratis; i++)
    {
        strcat(linea6,juegosGratis[i]);
        strcat(linea6,"\n");
    }
    strcpy(arregloFinal[5],linea6);
    //printf("%s\n", arregloFinal[5]);

    return arregloFinal;
    
}

// Entradas: void
// Salidas: Se retorna una lista del tipo TDAlista (lista enlazada)
// Descripción: Se inicializa un tipo de datos TDAlista otorgandole memoria inicial y una cabecera
TDAlista *crearListaVacia()
{
    TDAlista *lista = (TDAlista *)malloc(sizeof(TDAlista));
    lista->inicio = NULL;
    return lista;
}

// Entradas: lista enlazada
// Salidas: void
// Descripción: Se libera la memoria dinamica empleada para la lista enlazada
void liberarLista(TDAlista *lista)
{
    free(lista);
}

// Entradas: Se ingresa una lista enlazada y un dato entero (posición de línea en documento)
// Salidas: void
// Descripción: Se reserva la memoria suficiente para lograr introducir un nuevo nodo
//              a la lista enlazada
void insertarInicio(TDAlista *lista, int dato)
{
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->puntero = lista->inicio;
    lista->inicio = nuevo;
}

// Entradas: Se ingresa una lista enlazada
// Salidas: Se retorna un valor entero que indica si una lista es vacia o no
// Descripción: Si la cabecera apunta a un nulo, entonces la lista enlazada está vacia,
//              caso contrarío, posee elementos/nodos
int esListaVacia(TDAlista *lista)
{
    if (lista->inicio == NULL)
        return 1;
    else
        return 0;
}

// Entradas: Se ingresa una lista enlazada
// Salidas: Se retorna el primer dato ubicado en la lista enlazada (del primer nodo, primer dato)
// Descripción: Si la lista enlazada no está vacia, se apunta al primer nodo y se retorna su valor
int retornarDato(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        int dato = auxiliar->dato;
        auxiliar = auxiliar->puntero;
        return dato;
    }
    else
    {
        return -1;
    }
    return -1;
}

// Entradas: Se ingresa una lista enlazada
// Salidas: void
// Descripción: Si la lista enlazada no está vacia, mediante un auxiliar se apunta al segundo
//              nodo en la lista enlazada original retornando el auxiliar quien no contempla
//              el primer nodo de la lista enlazada original
void eliminarInicio(TDAlista *lista)
{
    nodo *auxiliar;
    if (!esListaVacia(lista))
    {
        auxiliar = lista->inicio;
        lista->inicio = lista->inicio->puntero;
        free(auxiliar);
    }
}

// Entradas: Se ingresa una lista enlazada
// Salidas: Se retorna el número de nodos en la lista enlazada
// Descripción: Si la lista no está vacia, se recorre empleando un ciclo while hasta finalizar
//              el recorrido mientras en paralelo se utiliza una variable acumuladora
//              en la cual figura el número de nodos
int nroNodosLista(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        int nroNodos = 0;
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            auxiliar = auxiliar->puntero;
            nroNodos++;
        }
        return nroNodos;
    }
    return 0;
}