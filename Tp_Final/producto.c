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

    while(getchar() != '\n');
    printf("Ingrese el nombre del producto: ");
    fgets(nuevo.nombreProducto, sizeof(nuevo.nombreProducto), stdin);
    nuevo.nombreProducto[strcspn(nuevo.nombreProducto, "\n")] = '\0';

    printf("Ingrese el precio del producto: ");
    scanf("%f", &nuevo.precio);

    printf("Ingrese el stock del producto: ");
    scanf("%d", &nuevo.stock);

    nuevo.activo = 1;

    return nuevo;
}

int verificarRepetidoArch (char nombreArch[], char productoBuscado[])
{
    FILE* archi = fopen(nombreArch, "rb");
    stProducto aux;
    int encontrado = -1;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stProducto),1,archi)>0)
        {
            if(strcasecmp(aux.nombreProducto, productoBuscado)== 0)
            {
                encontrado = 1;
            }
        }
        fclose(archi);
    }
    else
    {

        printf("El producto no se puede agregar porque ya existe");

    }
    return encontrado;
}

void cargarMuchosProductos (char nombreArch [], char productoBuscado[])
{
    FILE* archi = fopen(nombreArch, "ab");
    stProducto aux;
    char seguir = 's';
    if (archi != NULL)
    {
        while (seguir == 's')
        {
            aux = cargarUnProducto();
            int estaRepetido = verificarRepetidoArch(nombreArch, aux.nombreProducto);

            if (estaRepetido == -1)
            {
                fwrite(&aux, sizeof(stProducto), 1, archi);

                printf("¿Desea cargar otro producto?: (s/n)");
                scanf(" %c", &seguir);
            }
            else
            {
                printf("\nEl producto no puede ser agreado porque ya existe\n");
            }
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

    printf("\nId: %d", nuevo.idProducto);

    printf("\nProdcuto: %s", nuevo.nombreProducto);

    printf("\nPrecio %f", nuevo.precio);

    printf("\nStock: %d", nuevo.stock);

    printf("\nActivo: %d", nuevo.activo);

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

int buscarPosMenorNombre (stProducto producto[], int val, int posInicial)
{

    int i = posInicial;
    char nombreMenor [50];
    strcpy(nombreMenor, producto[i].nombreProducto);
    int posMenor = i;

    for (i = posInicial + 1; i < val; i++)
    {

        if (strcmp(producto[i].nombreProducto, nombreMenor) < 0)
        {
            strcpy(nombreMenor, producto[i].nombreProducto);
            posMenor = i;
        }
    }
    return posMenor;
}

void ordenarNombreProducto(stProducto producto[], int val)
{

    int j;
    stProducto aux;
    int posMenor;

    for (j = 0; j < val - 1; j++)
    {
        posMenor = buscarPosMenorNombre(producto, val, j);
        aux = producto[j];
        producto[j] = producto[posMenor];
        producto[posMenor] = aux;
    }
}

void gestionarProductos(char nombreArch[])
{
    int opcion;
    char nombreProducto[30];
    float nuevoPrecio;
    float precioFiltro;

    do
    {
        printf("\n--- GESTION DE PRODUCTOS ---\n");
        printf("1. Alta de producto\n");
        printf("2. Baja de producto\n");
        printf("3. Modificar precio\n");
        printf("4. Consultar por precio menor a\n");
        printf("5. Listar todos los productos\n");
        printf("0. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n');

        switch(opcion)
        {
        case 1:
            cargarMuchosProductos(nombreArch,nombreProducto);
            break;

        case 2:
            printf("Ingrese el nombre del producto que desea dar de baja: ");
            fgets(nombreProducto, 30, stdin);
            nombreProducto[strcspn(nombreProducto, "\n")] = '\0';

            if(bajaLogicaProducto(nombreArch, nombreProducto) == 1)
            {
                printf("Producto dado de baja con exito.\n");
            }
            else
            {
                printf("No se encontro el producto.\n");
            }
            break;

        case 3:
            printf("Ingrese el nombre del producto a modificar: ");
            fgets(nombreProducto, 30, stdin);
            nombreProducto[strcspn(nombreProducto, "\n")] = '\0';

            printf("Ingrese el nuevo precio: ");
            scanf("%f", &nuevoPrecio);
            while(getchar() != '\n');

            modificarPrecioDelProducto(nombreArch, nombreProducto, nuevoPrecio);
            printf("Precio modificado con exito.\n");
            break;

        case 4:
            printf("Ingrese el precio que desea filtrar: ");
            scanf("%f", &precioFiltro);
            while(getchar() != '\n');

            consultarPorPrecioMenorAlPasado(nombreArch, precioFiltro);
            break;

        case 5:
            mostrarMuchosProductos(nombreArch);
            break;
        }
    }
    while(opcion != 0);
}
