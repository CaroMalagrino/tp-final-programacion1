#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "producto.h"

stProducto cargarUnProducto ()
{

    stProducto nuevo;

    printf("Ingrese el id del producto: ");
    scanf("%d", &nuevo.idProducto);

    printf("Ingrese el nombre del producto: ");
    fflush(stdin);
    fgets(nuevo.nombreProducto, 30, stdin);
    nuevo.nombreProducto[strcspn(nuevo.nombreProducto, "\n")] = '\0';

    printf("Ingrese el precio del producto: ");
    scanf("%f", &nuevo.precio);

    printf("Ingrese el stock del producto: ");
    scanf("%d", &nuevo.stock);

    nuevo.activo = 1;

    return nuevo;
}

void cargarMuchosProductos (char nombreArch [])
{

    FILE* archi = fopen(nombreArch, "ab");
    stProducto aux;
    char seguir = 's';
    if (archi != NULL)
    {
        while (seguir == 's')
        {
            aux = cargarUnProducto();
            fwrite(&aux, sizeof(stProducto), 1, archi);

            printf("¿Desea cargar otro producto?: (s/n)");
            scanf(" %c", &seguir);
        }

        fclose(archi);
    }
    else
    {
        printf("El archivo no existe o no pudo abrirse");

    }

}


void mostrarUnProducto (stProducto nuevo)
{

    printf("Id: %d", nuevo.idProducto);

    printf("Prodcuto: %s", nuevo.nombreProducto);

    printf("Precio %f", nuevo.precio);

    printf("Stock: %d", nuevo.stock);

    printf("Activo: %d", nuevo.activo);

}

void mostrarMuchosProductos (char nombreArch[])
{

    FILE* archi = fopen(nombreArch, "rb");
    stProducto aux;
    if (archi != NULL)
    {
        while (fread(&aux, sizeof(stProducto), 1, archi) > 0)
        {

            mostrarUnProducto(aux);
        }
        fclose(archi);
    }
    else
    {
        printf("El archivo no existe o no pudo abrirse");
    }
}

int buscarPosProducto (char nombreArch[], char productoBuscado[])
{

    FILE* archi = fopen(nombreArch, "rb");
    stProducto aux;
    int encontrado = 0;
    int posProducto = -1;
    int i = 0;
    if (archi != NULL)
    {
        while(fread(&aux, sizeof(stProducto),1,archi) > 0)
        {

            if (strcasecmp(aux.nombreProducto, productoBuscado) == 0)
            {
                encontrado = 1;
                posProducto = i;
            }
            i++;
        }
        fclose(archi);
    }
    else
    {
        printf("El archivo no existe o no pudo abrirse");
    }
    return posProducto;
}

int bajaLogicaProducto (char nombreArch[], char productoBuscado[])
{
    int pos = buscarPosProducto(nombreArch, productoBuscado);
    int eliminadoConExito = 0;
    if (pos != -1)
    {
        FILE* archi = fopen(nombreArch, "r+b");
        stProducto aux;

        if (archi != NULL)
        {
            fseek(archi, sizeof(stProducto)* pos, SEEK_SET);

            fread(&aux, sizeof(stProducto), 1, archi);

            aux.activo = 0;

            fseek(archi, -sizeof(stProducto), SEEK_CUR);

            fwrite(&aux, sizeof(stProducto), 1, archi);

            fclose(archi);
            eliminadoConExito = 1;
        }
        else
        {
            printf("El archivo no existe o no pudo abrirse");
        }
    }
    return eliminadoConExito;
}

void modificarPrecioDelProducto (char nombreArch[], char productoBuscado[], float nuevoPrecio)
{
    int pos = buscarPosProducto(nombreArch, productoBuscado);
    if (pos != -1)
    {
        FILE* archi = fopen(nombreArch, "r+b");
        stProducto aux;
        if (archi != NULL)
        {
            fseek(archi, sizeof(stProducto)*pos, SEEK_SET);

            fread(&aux, sizeof(stProducto), 1, archi);

            aux.precio = nuevoPrecio;

            fseek(archi, -sizeof(stProducto), SEEK_CUR);

            fwrite(&aux, sizeof(stProducto), 1, archi);

            fclose(archi);
        }
        else
        {
            printf("El archivo no existe o no pudo abrirse");
        }
    }
}

void consultarPorPrecioMenorAlPasado (char nombreArch[], float precioAFiltrar)
{

    FILE* archi = fopen(nombreArch, "rb");
    stProducto aux;
    if (archi!= NULL)
    {
        while(fread(&aux, sizeof(stProducto), 1, archi) > 0)
        {

            if (aux.precio < precioAFiltrar && aux.activo == 1)
            {
                mostrarUnProducto(aux);
            }
        }

        fclose(archi);
    }
    else
    {
        printf("El archivo no existe o no pudo abrirse");
    }

}

int pasarProductosAArreglo(char nombreArch[], stProducto productos[], int dimension)
{

    FILE* archi = fopen(nombreArch, "rb");
    int validos = 0;
    stProducto aux;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stProducto), 1, archi) > 0)
        {
            if(validos < dimension && aux.activo == 1)
            {

                productos[validos] = aux;
                validos++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("El archivo no existe o no pudo abrirse");
    }
    return validos;
}

int buscarPosMenorPrecio (stProducto producto[], int val, int posInicial)
{

    int i = posInicial;
    int menor = producto[i].precio;
    int posMenor = i;

    for (i = posInicial; i < val; i++)
    {

        if (menor > producto[i].precio)
        {
            menor = producto[i].precio;
            posMenor = i;
        }
    }
    return posMenor;
}

void ordenarPrecioDeMenorAMayor (stProducto producto[], int val){

int j;
stProducto aux;
int posMenor;

for (j = 0; j < val; j++){
    posMenor = buscarPosMenorPrecio(producto, val, j);
    aux = producto[j];
        producto[j] = producto[posMenor];
        producto[posMenor] = aux;
}
}
