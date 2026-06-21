#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

typedef struct {
    int idProducto;                 // Identificador único (autoincremental o código)
    char nombreProducto[30]; // Nombre del artículo (dimensión 30, ideal para fgets)
    float precio;                   // Precio unitario del producto
    int stock;                      // Cantidad disponible en el depósito
    int activo;                     // 1 para Alta / 0 para Baja Lógica
} stProducto;
#endif
