#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "producto.h"
#include "usuario.h"
#include "carrito.h"
#include "pila.h"

stProducto buscarProduEnArch (char nombreArch[], char productoBuscado[])
{
    stProducto aux;
    int posProducto = buscarPosProducto(nombreArch, productoBuscado);
    stProducto encontrado;
    encontrado.idProducto = -1;

    if (posProducto != -1)
    {
        FILE* archi = fopen(nombreArch, "rb");
        if (archi != NULL)
        {
            fseek(archi, sizeof(stProducto)*posProducto, SEEK_SET);
            if (fread(&aux, sizeof(stProducto),1,archi)>0)
            {
                if (aux.activo == 1)
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
    }
    return encontrado;
}

int verificarRepetido (char nombreArch[], char productoBUscado[],stItemCarrito carrito[], int val)
{
    stProducto producto = buscarProduEnArch(nombreArch, productoBUscado);
    int encontrado = -1;
    int i = 0;

    if(producto.idProducto != -1)
    {
        while (i < val)
        {
            if (producto.idProducto == carrito[i].producto.idProducto)
            {
                encontrado = i;
            }
            i++;
        }
    }
    return encontrado;
}

int verificarStock (char nombreArch[], char productoABuscar[], int cantidadAComparar)
{

    stProducto producto = buscarProduEnArch(nombreArch, productoABuscar);
    int hayStock = 0;

    if(cantidadAComparar <= producto.stock && producto.idProducto != -1)
    {
        hayStock = 1;

    }
    return hayStock;
}

int buscarPosEnCarrito (stItemCarrito* carrito, int val, char productoBuscado[])
{
    int i = 0;
    int posProductoBuscado = -1;

    for (i = 0; i < val; i++)
    {
        if (strcasecmp(carrito[i].producto.nombreProducto, productoBuscado) == 0)
        {
            posProductoBuscado = i;
        }
    }
    return posProductoBuscado;
}

/*void mostrarUnSoloItemDelCarrito (stItemCarrito *carrito){

//float subTotal = "Llamar funcion que calcula esto. La pila con la recursiva"
printf("\n____________________________________\n");
printf("")

}
*/

int agregarUnProductoAlCarrito (char nombreArch[], stItemCarrito** carrito, char productoDeseado[], int cantidadDeseada, int valActual)
{
    stProducto producto = buscarProduEnArch(nombreArch, productoDeseado);
    int hayStock = verificarStock(nombreArch, productoDeseado, cantidadDeseada);
    int estaRepetido = verificarRepetido(nombreArch,productoDeseado,*carrito,valActual);


    if (producto.idProducto != -1 && hayStock != 0 )
    {
        *carrito = malloc (sizeof(stItemCarrito));
        if (estaRepetido != -1)
        {
            *carrito = realloc(*carrito, sizeof(stItemCarrito) * (valActual + 1));
            (*carrito)[valActual].producto = producto;
            (*carrito)[valActual].cantidad = cantidadDeseada;
            valActual++;
        }
        else
        {
            (*carrito)[valActual].cantidad += cantidadDeseada;
        }
    }

    return valActual;
}

int eliminarProductoDelCarrito (char productoBuscado[], stItemCarrito** carrito, int valActual)
{
    int posProducto = buscarPosEnCarrito(*carrito, valActual, productoBuscado);

    if (posProducto != -1)
    {
        for (int i = posProducto; i < valActual - 1; i++)
        {
            (*carrito)[i] = (*carrito)[i + 1];

        }
        *carrito = realloc(*carrito, sizeof(stItemCarrito) * (valActual - 1));
        valActual--;
    }
    return valActual;
}

//Se le pasa la pos que devuelve la de arriba.
int modificarCantidadCarrito(char nombreArch[], stItemCarrito** carrito, char productoDeseado[], int cantidadNueva, int valActual)
{
    int pos = buscarPosEnCarrito(*carrito, valActual, productoDeseado);
    int pudoModificar = 0;

    if (pos != -1)
    {
        if (cantidadNueva == 0)
        {
            valActual = eliminarProductoDelCarrito(productoDeseado, carrito, valActual);
            pudoModificar = 1;
        }
        else
        {
            int hayStock = verificarStock(nombreArch, productoDeseado, cantidadNueva);
            if (hayStock == 1)
            {
                (*carrito)[pos].cantidad = cantidadNueva;
                pudoModificar = 1;
            }
        }
    }
    return valActual;
}


void gestionarPago (stItemCarrito* carrito, int val, Pila* precios)
{
    float subTotal = 0;
    for (int i = 0; i < val; i++)
    {

        subTotal = carrito[i].producto.precio * carrito[i].cantidad;
        apilar(precios, subTotal);
    }
}

float sumaTotal (Pila* precios){
float totalAPagar = 0;
if (!pilavacia(precios)){

    float precioActual = desapilar(precios);
    totalAPagar = precioActual + sumaTotal(precios);
}

return totalAPagar;
}

void mostrarCarrito(stItemCarrito* carrito, int validos)
{
    float subtotal = 0;
    float totalAcumulado = 0;

    if(validos == 0)
    {
        printf("Tu carrito esta vacio.");
    }
    else
    {
        for(int i = 0; i < validos; i++)
        {
            subtotal = carrito[i].cantidad * carrito[i].producto.precio;

            totalAcumulado += subtotal;

            printf("Producto: %s", carrito[i].producto.nombreProducto);
            printf("Cantidad: %d", carrito[i].cantidad);
            printf("Precio por unidad: $%.2f", carrito[i].producto.precio);
            printf("Subtotal: $%.2f", subtotal);
        }
        printf("Total Acumulado: $%.2f\n", totalAcumulado);
    }
}
