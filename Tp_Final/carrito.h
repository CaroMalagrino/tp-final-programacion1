#ifndef CARRITO_H_INCLUDED
#define CARRITO_H_INCLUDED
#include "pila.h"
#include "producto.h"

typedef struct {
    stProducto producto;
    int cantidad;
} stItemCarrito;

stProducto buscarProduEnArch (char nombreArch[], char productoBuscado[]);
int verificarRepetido (char nombreArch[], char productoBUscado[],stItemCarrito carrito[], int val);
int verificarStock (char nombreArch[], char productoABuscar[], int cantidadAComparar);
int buscarPosEnCarrito (stItemCarrito* carrito, int val, char productoBuscado[]);
int agregarUnProductoAlCarrito (char nombreArch[], stItemCarrito** carrito, char productoDeseado[], int cantidadDeseada, int valActual);
int eliminarProductoDelCarrito (char productoBuscado[], stItemCarrito** carrito, int valActual);
int modificarCantidadCarrito(char nombreArch[], stItemCarrito** carrito, char productoDeseado[], int cantidadNueva, int valActual);
void gestionarPago (stItemCarrito* carrito, int val, Pila* precios);
float sumaTotal (Pila* precios);
void mostrarCarrito(stItemCarrito* carrito, int validos);
void modificarStockEnArchivo (char nombreArch[], stItemCarrito carrito[], int val);
void gestionarCarrito(char archivoUsuarios[], char nombreArch[], stItemCarrito** carrito, int* validos);

#endif
