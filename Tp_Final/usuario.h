#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct
{
    int id;
    char nombre[50];
    char mail[50];
    char telefono[20];
    char contrasena[30];
    int activo;
} stUsuario;


stUsuario cargarUnUsuario();
void cargarMuchosUsuarios(char nombreArchivo[]);
void mostrarUnUsuario(stUsuario nuevo);
void guardarUsuarioEnArchivo(char nombreArchivo[], stUsuario nuevo);
void mostrarUsuariosEnArchivo(char nombreArchivo[]);
void logicaUser(char nombreArchivo[], int idBaja);
int loginUser(char nombreArchivo[], char mailIngresado[], char passIngresada[]);
void consultarPorNombre(char nombreArchivo[], char nombreBuscado[]);
void modificarTelefonoUsuario(char nombreArchivo[], int idModificar);
int pasarDatosAMatriz(char nombreArchivo[], char matriz[][50]);
int existeEnMatriz(char matriz[][50], int validos, char textoBuscado[]);
void ordenarPorSeleccion(stUsuario arr[], int validos);

#endif // USUARIO_H_INCLUDED
