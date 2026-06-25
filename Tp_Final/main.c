#include <stdio.h>
#include <stdlib.h>
#include "producto.h"
#include "usuario.h"
#include "carrito.h"
#include "pila.h"

int main()
{
    stItemCarrito* carrito;
    int validos = 0;
    int opcion;

    do
    {
        printf("\n---== MENU PRINCIPAL ==---\n");
        printf(" 1. Gestionar carrito\n");
        printf(" 2. Gestionar productos\n");
        printf(" 3. Gestionar usuarios\n");
        printf(" 0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n');

        switch(opcion)
        {
        case 1:
            gestionarCarrito("usuarios.dat", "productos.dat",&carrito, &validos);
            break;

        case 2:
            gestionarProductos("productos.dat");
            break;

        case 3:
            gestionarUsuarios("usuarios.dat");
            break;

        case 0:
            printf("Saliendo del sistema.\n");
            break;

        default:
            printf("Opcion invalida.\n");
            break;
        }
    }
    while(opcion != 0);

    if(carrito != NULL)
    {
        free(carrito);
    }

    return 0;
}
