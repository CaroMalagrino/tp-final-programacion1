#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "producto.h"
#include "usuario.h"

stProducto buscarProduEnArch (char nombreArch[], char productoBuscado[])
{

    FILE* archi = fopen(nombreArch, "rb");
    stProducto aux;
    stProducto encontrado;
    if (archi != NULL)
    {
        while(fread(&aux, sizeof(stProducto), 1, archi) > 0)
        {
            if(strcasecmp(aux.nombreProducto, productoBuscado) == 0)
            {
                encontrado = aux;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("¿Desea cargar otro producto?: (s/n)");
    }
    return encontrado;
}
