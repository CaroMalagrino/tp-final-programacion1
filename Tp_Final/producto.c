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
        printf("El archivo no se existe o no pudo abrirse");

    }

}








