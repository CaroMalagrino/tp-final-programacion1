#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

typedef struct {
    int idProducto;
    char nombreProducto[30];
    float precio;
    int stock;
    int activo;
} stProducto;

stProducto cargarUnProducto ();
void cargarMuchosProductos (char nombreArch []);
void mostrarUnProducto (stProducto nuevo);
void mostrarMuchosProductos (char nombreArch[]);
int buscarPosProducto (char nombreArch[], char productoBuscado[]);
int bajaLogicaProducto (char nombreArch[], char productoBuscado[]);
void modificarPrecioDelProducto (char nombreArch[], char productoBuscado[], float nuevoPrecio);
void consultarPorPrecioMenorAlPasado (char nombreArch[], float precioAFiltrar);
int pasarProductosAArreglo(char nombreArch[], stProducto productos[], int dimension);
int buscarPosMenorNombre (stProducto producto[], int val, int posInicial);
void ordenarNombreProducto(stProducto producto[], int val);
void gestionarProductos(char nombreArch[]);

#endif
