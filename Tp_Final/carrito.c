#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "producto.h"
#include "usuario.h"
#include "carrito.h"

stProducto buscarProduEnArch (char nombreArch[], char productoBuscado[])
{

    FILE* archi = fopen(nombreArch, "rb");
    stProducto aux;
    stProducto encontrado;
    encontrado.idProducto = -1;
    if (archi != NULL)
    {
        while(fread(&aux, sizeof(stProducto), 1, archi) > 0)
        {
            if(strcasecmp(aux.nombreProducto, productoBuscado) == 0 && aux.activo == 1)
            {
                encontrado = aux;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("El archivo no existe o no pudo abrirse");
    }
    return encontrado;
}

int verificarRepetido (char nombreArch[], char productoBUscado[],stItemCarrito* carrito, int val)
{
    stProducto producto = buscarProduEnArch(nombreArch, productoBUscado);
    int encontrado = -1;
    int i = 0;

    while (i < val && producto.activo == 1)
    {
        if (producto.idProducto == carrito[i].producto.idProducto)
        {
            encontrado = i;
        }
        i++;
    }
    return encontrado;
}

int verificarStock (char nombreArch[], char productoABuscar[], int cantidadAComparar){

stProducto producto = buscarProduEnArch(nombreArch, productoABuscar);
int hayStock = 0;

if(cantidadAComparar <= producto.stock && producto.idProducto != -1){
    hayStock = 1;

}
return hayStock;
}
//m
