#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

stUsuario cargarUnUsuario()
{
    stUsuario nuevo;

    printf("Ingrese el ID del usuario: ");
    scanf("%d", &nuevo.id);

    while(getchar() != '\n');

    printf("Ingrese el nombre: ");
    fgets(nuevo.nombre,sizeof(nuevo.nombre), stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

    // aca iria la de normalizar texto

    printf("Ingrese el correo electronico: ");
    fgets(nuevo.mail, sizeof(nuevo.mail), stdin);
    nuevo.mail[strcspn(nuevo.mail, "\n")] = 0;

    printf("Ingrese el telefono: ");
    fgets(nuevo.telefono, sizeof(nuevo.telefono), stdin);
    nuevo.telefono[strcspn(nuevo.telefono, "\n")] = 0;

    printf("Ingrese la contrasena: ");
    fgets(nuevo.contrasena, sizeof(nuevo.contrasena), stdin);
    nuevo.contrasena[strcspn(nuevo.contrasena, "\n")] = 0;

    nuevo.activo = 1;

    return nuevo;
}

void cargarMuchosUsuarios(char nombreArchivo[])
{
    char opcion = 's';
    stUsuario nuevo;
    FILE* archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        while(opcion == 's' || opcion == 'S')
        {
            nuevo = cargarUnUsuario();
            fwrite(&nuevo, sizeof(stUsuario), 1, archi);

            printf("Desea cargar otro usuario? s/n: ");
            scanf(" %c", &opcion);
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo. ");
    }
}

void mostrarUnUsuario(stUsuario nuevo)
{
    if(nuevo.activo == 1)
    {
     printf("ID: %d\n", nuevo.id);
     printf("Nombre: %s\n", nuevo.nombre);
     printf("Mail: %s\n", nuevo.mail);
     printf("Telefono: %s\n", nuevo.telefono);
     printf("Contrasena: %s\n", nuevo.contrasena);
    }
}

void guardarUsuarioEnArchivo(char nombreArchivo[], stUsuario nuevo)
{
    FILE* archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        fwrite(&nuevo,sizeof(stUsuario),1, archi);
        fclose(archi);
    } else{
    printf("No se pudo abrir el archivo.");
    }
}

void mostrarUsuariosEnArchivo(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stUsuario aux;

    if(archi != NULL)
    {
        while(fread(&aux,sizeof(stUsuario),1,archi) > 0)
        {
            mostrarUnUsuario(aux);
        }
        fclose(archi);
    } else{
    printf("No se pudo abrir el archivo.");
    }
}
