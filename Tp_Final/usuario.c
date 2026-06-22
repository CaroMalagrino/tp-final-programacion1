#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"


//PARA CUMPLIR CON ALTA
stUsuario cargarUnUsuario(char nombreArchivo[])
{
    stUsuario nuevo;
    char matrizValidacion[100][50];
    int validosMatriz = pasarDatosAMatriz(nombreArchivo, matrizValidacion);

    printf("Ingrese el ID del usuario: ");
    scanf("%d", &nuevo.id);

    while(getchar() != '\n');

    printf("Ingrese el nombre: ");
    fgets(nuevo.nombre,sizeof(nuevo.nombre), stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

    //BUCLE PARA VALIDAR, NOSE SI ESTA BIEN

    do
    {
        printf("Ingrese el correo electronico: ");
        fgets(nuevo.mail, sizeof(nuevo.mail), stdin);
        nuevo.mail[strcspn(nuevo.mail, "\n")] = 0;

        if(existeEnMatriz(matrizValidacion, validosMatriz, nuevo.mail) == 1)
        {
            printf("Error: Ese mail ya esta registrado. Intente con otro.\n");
        }
    }
    while(existeEnMatriz(matrizValidacion, validosMatriz, nuevo.mail) == 1);

    // aca iria la de normalizar texto
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
            nuevo = cargarUnUsuario(nombreArchivo);
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

//CUMPLE CON LISTA
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
    }
    else
    {
        printf("No se pudo abrir el archivo.");
    }
}

//PARTE DE LISTA TAMBIEN
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
    }
    else
    {
        printf("No se pudo abrir el archivo.");
    }
}

// CUMPLE CON BAJA
void logicaUser(char nombreArchivo[], int idBaja)
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stUsuario aux;

    int encontrado = 0;

    if(archi != NULL)
    {
        while(encontrado == 0 && fread(&aux,sizeof(stUsuario),1,archi) > 0)
        {
            if(aux.id == idBaja && aux.activo == 1)
            {
                aux.activo = 0;

                fseek(archi, sizeof(stUsuario) * -1, SEEK_CUR);

                fwrite(&aux, sizeof(stUsuario), 1, archi);

                encontrado = 1;
            }
        }
        fclose(archi);

        if(encontrado == 1)
        {
            printf("El usuario ID %d se ha dado de baja.", idBaja);
        }
    }
}

//CUMPLE CONSULTA

int loginUser(char nombreArchivo[], char mailIngresado[], char passIngresada[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stUsuario aux;
    int idLogeado = -1;

    if(archi != NULL)
    {
        while(fread(&aux,sizeof(stUsuario), 1, archi) > 0)
        {
            if(strcmp(aux.mail, mailIngresado) == 0 && strcmp(aux.contrasena, passIngresada) == 0)
            {
                idLogeado = aux.id;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo.");
    }
    return idLogeado;
}

void consultarPorNombre(char nombreArchivo[], char nombreBuscado[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stUsuario aux;
    int encontrado = 0;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stUsuario), 1, archi) > 0)
        {
            if(strcmp(aux.nombre, nombreBuscado) == 0 && aux.activo == 1)
            {
                mostrarUnUsuario(aux);
                encontrado = 1;
            }
        }
        fclose(archi);

        if(encontrado == 0)
        {
            printf("No hay un usuario con ese nombre.");
        }
    }
    else
    {
        printf("Error al abrir el archivo.");
    }
}
//CUMPLE CON MODIFICAICON
void modificarTelefonoUsuario(char nombreArchivo[], int idModificar)
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stUsuario aux;
    int encontrado = 0;

    if(archi != NULL)
    {
        while(encontrado == 0 && fread(&aux, sizeof(stUsuario), 1, archi) > 0)
        {
            if(aux.id == idModificar && aux.activo == 1)
            {
                printf("Usuario: %s", aux.nombre);
                printf("Ingrese el nuevo telefono: ");

                while(getchar() != '\n');

                fgets(aux.telefono, sizeof(aux.telefono), stdin);
                aux.telefono[strcspn(aux.telefono, "\n")] = '\0';

                fseek(archi, sizeof(stUsuario) * -1, SEEK_CUR);
                fwrite(&aux, sizeof(stUsuario), 1, archi);

                encontrado = 1;
            }
        }
        fclose(archi);
        if(encontrado == 1)
        {
            printf("Elt elefono se modifico.");
        }
        else
        {
            printf("Error al cambiar.");
        }
    }
    else
    {

        printf("No se pudo abrir el archivo.");
    }
}

int pasarDatosAMatriz(char nombreArchivo[], char matriz[][50])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stUsuario aux;
    int validos = 0;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stUsuario),1, archi) > 0)
        {
            if(aux.activo == 1)
            {
                strcpy(matriz[validos], aux.mail);
                validos++;
            }
        }
        fclose(archi);
    }
    return validos;
}

int existeEnMatriz(char matriz[][50], int validos, char textoBuscado[])
{
    int encontrado = 0;
    for(int i = 0; i < validos; i++)
    {
        if(strcmpi(matriz[i], textoBuscado) == 0)
        {
            encontrado = 1;
        }
    }
    return encontrado;
}

void ordenarPorSeleccion(stUsuario arr[], int validos)
{
    stUsuario aux;
    int posMenor;

    for(int i = 0; i < validos - 1; i++)
    {
        posMenor = i;
        for(int j = i + 1; j < validos; j++)
        {
            if(strcmpi(arr[j].nombre, arr[posMenor].nombre) < 0)
            {
                posMenor = j;
            }
        }
        if(posMenor != i)
        {
            aux = arr[i];
            arr[i] = arr[posMenor];
            arr[posMenor] = aux;
        }
    }
}

void insertarOrdenadorPorId(stUsuario arr[], int validos, stUsuario dato)
{
    int i = validos -1;

    while(i >= 0 && arr[i].id > dato.id)
    {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = dato;
}

void ordenarPorInserccionId(stUsuario arr[], int validos)
{
    stUsuario aux;

    for(int i = 1; i < validos; i++)
    {
        aux = arr[i];
        insertarOrdenadorPorId(arr, i, aux);
    }
}
