#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct Pila {
    float valores[50];
    int postope;
} Pila;

void inicpila(Pila* p);
void apilar(Pila* p, int dato);
float desapilar(Pila* p);
float tope(Pila* p);
int pilavacia(Pila* p);
void leer(Pila* p);
void mostrar(Pila* p);

#endif // PILA_H_INCLUDED
