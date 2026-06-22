#ifndef CARRITO_H_INCLUDED
#define CARRITO_H_INCLUDED

typedef struct {
    int idProducto;
    char nombreProducto[50];
    int cantidad;
    float precioUnitario;
    float subtotal;
} stItemCarrito;

#endif
