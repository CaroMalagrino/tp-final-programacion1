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
void guardarUsuarioEnArchivo(char archivo[], stUsuario nuevo);

#endif // USUARIO_H_INCLUDED
