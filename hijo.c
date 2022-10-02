#include "hijo.h"

char *copiarStringHijo(char string[])
{
    char *str;
    str = (char *)malloc(300);
    strcpy(str, string);
    return (char *)str;
}

float promedio(int arr[], int largoArr)
{
    float sumaTotal = 0;
    for (int i = 0; i < largoArr; i++)
    {
        sumaTotal = sumaTotal + arr[i];
    }
    return sumaTotal / largoArr;
}

float porcentaje(int total, int nro)
{
    float porcentaje;
    porcentaje = (nro * 100) / total;
    return porcentaje;
}

void calculos(TDAlista *lista)
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
    int nroJuegosW = 0, nroJuegosM = 0, nroJuegosL = 0;
    float porcentajeWs, porcentajeMc, porcentajeLx;
    int preciosAnio[cantNodos];
    float promPreciosAnio;
    int nroJuegosGratis = 0;
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
                printf("ESTOY COMPARANDO %s CON %s\n", comparador, esGratis);
                if (strcmp(esGratis, comparador) == 0)
                {
                    nroJuegosGratis++;
                }
            }
            iter = iter + 1;
        }
    }
    char *juegosGratis[nroJuegosGratis];
    int contador = 0;
    posicionGratis = 6;
    promPreciosAnio = promedio(preciosAnio, cantNodos);
    porcentajeWs = porcentaje((nroJuegosW + nroJuegosM + nroJuegosL), nroJuegosW);
    porcentajeMc = porcentaje((nroJuegosW + nroJuegosM + nroJuegosL), nroJuegosM);
    porcentajeLx = porcentaje((nroJuegosW + nroJuegosM + nroJuegosL), nroJuegosL);
    printf("NUIRMERO JUEGOS GRAITS: %d\n", nroJuegosGratis);
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

    for (int i = 0; i < nroJuegosGratis; i++)
    {
        printf("Juego gratis: %s\n", juegosGratis[i]);
    }

    exit(printf("FINALIZADA LA TAREA DEL HIJO\n"));
}

/*//////////////////////////////////////////////////////////////////////////*/

TDAlista *crearListaVacia()
{
    TDAlista *lista = (TDAlista *)malloc(sizeof(TDAlista));
    lista->inicio = NULL;
    return lista;
}

void liberarLista(TDAlista *lista)
{
    free(lista);
}

void insertarInicio(TDAlista *lista, int dato)
{
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->puntero = lista->inicio;
    lista->inicio = nuevo;
}

int esListaVacia(TDAlista *lista)
{
    if (lista->inicio == NULL)
        return 1;
    else
        return 0;
}

void recorrerLista(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            printf("%d ", auxiliar->dato);
            auxiliar = auxiliar->puntero;
        }
        printf("\n");
    }
    else
        printf("La lista está vacía\n");
}

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
