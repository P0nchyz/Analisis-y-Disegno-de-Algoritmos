#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "huffman.h"

void Obtener_Valor(Arbol A, int *cont, HuffmanCode h, Code *table);

Arbol Crear_Nodo(unsigned char c, int f)
{
	Arbol retArbol= malloc(sizeof(struct Nodo));
	retArbol->c = c;
	retArbol->f = f;
	retArbol->izq = retArbol->der = NULL;
	
	return retArbol;
}


Arbol Comb_Arbol(Arbol A, Arbol B)
{
	Arbol retArbol= malloc(sizeof(struct Nodo)); 
	retArbol->f = A->f + B->f;
	retArbol->izq = (A->f >= B->f) ? B : A; // Si A > B guardamos B, si no A
	retArbol->der = (A->f < B->f) ? B : A; // Si A > B guardamos A, si no B
	return retArbol;
}

/*
void Print_Arbol(Arbol A, int aux, int length)
{
	if (A->der == NULL || A->izq == NULL) {
		//printf("%c\t --- ", A->c);
		//printBinary(aux, length);
		//printf("\n");
		return;
	}
	int leftAux = aux;
	int rightAux = aux;
	Print_Arbol(A->izq, (leftAux << 1) | 0, length + 1);
	Print_Arbol(A->der, (rightAux << 1) | 1, length + 1);
}
*/

void printBinary(unsigned char *num, int bits) {
    for (int i = 0; i < bits; i++) {
        printf("%d", num[i]);
    }
}

Code *Obtener_Tabla(Arbol A, int num)
{
	Code *retCode = malloc(num * sizeof(*retCode));
	int cont = 0;
	HuffmanCode aux = {.length = 0, .num = NULL};
	Obtener_Valor(A, &cont, aux, retCode);
	return retCode;
}

void Obtener_Valor(Arbol A, int *cont, HuffmanCode h, Code *table)
{
	if (A->der == NULL || A->izq == NULL) {
		table[*cont].c = A->c;
		table[*cont].h = h;
		(*cont)++;
		return;
	}
	HuffmanCode leftAux = {
		.length = h.length + 1,
		.num = malloc(leftAux.length * sizeof(*leftAux.num))};
	for (int i = 0; i < h.length; i++) { // Copiamos los valores
		leftAux.num[i] = h.num[i];
	}
	leftAux.num[leftAux.length - 1] = 0;
	Obtener_Valor(A->izq, cont, leftAux, table);

	HuffmanCode rightAux = {
		.length =h .length + 1,
		.num = malloc(rightAux.length * sizeof(*rightAux.num))
		};
	for (int i = 0; i < h.length; i++) { // Copiamos los valores
		rightAux.num[i] = h.num[i];
	}
	rightAux.num[leftAux.length - 1] = 1;
	Obtener_Valor(A->der, cont, rightAux, table);
}