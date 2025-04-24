#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Nodo{
	struct  Nodo * izq;
	struct Nodo * der;
	unsigned char caracter;
	int frecuencia;
};

typedef struct Nodo* Arbol;

Arbol Crear_Nodo(unsigned char caracter, int frecuencia)
{
	Arbol retArbol= malloc(sizeof(struct Nodo));
	retArbol->caracter= caracter;
	retArbol->frecuencia= frecuencia;
	retArbol->izq=retArbol->der=NULL;
	
	return retArbol;
}


Arbol Comb_Arbol(Arbol A, Arbol B)
{
	Arbol retArbol= malloc(sizeof(struct Nodo)); 
	retArbol->frecuencia = A->frecuencia + B->frecuencia;
	retArbol->izq = (A->frecuencia >= B->frecuencia) ? B : A; // Si A > B guardamos B, si no A
	retArbol->der = (A->frecuencia < B->frecuencia) ? B : A; // Si A > B guardamos A, si no B
	return retArbol;
}