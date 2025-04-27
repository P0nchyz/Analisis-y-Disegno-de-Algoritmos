#include <ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "huffman.h"

void Obtener_Valor(Arbol A, int *cont, HuffmanCode h, Code *table);

Arbol Crear_Nodo(uint8_t c, int f)
{
	Arbol retArbol= malloc(sizeof(struct Nodo));
	retArbol->c = c;
	retArbol->f = f;
	retArbol->izq = retArbol->der = NULL;
	
	return retArbol;
}

bool Es_Hoja(Arbol A)
{
	if (A->der == NULL || A->izq == NULL)
		return true;
	else
		return false;
}

Arbol Comb_Arbol(Arbol A, Arbol B)
{
	Arbol retArbol= malloc(sizeof(struct Nodo)); 
	retArbol->f = A->f + B->f;
	retArbol->izq = (A->f >= B->f) ? B : A; // Si A > B guardamos B, si no A
	retArbol->der = (A->f < B->f) ? B : A; // Si A > B guardamos A, si no B
	return retArbol;
}

Arbol Construir_Arbol(Arbol *nodos, int numNodos)
{
	for (int i = 0; i < numNodos - 1; i++) {
		nodos[i + 1] = Comb_Arbol(nodos[i], nodos[i + 1]);
		for (int j = i + 1; j < numNodos - 1; j++) {
			if (nodos[j]->f < nodos[j + 1]->f)
				break;
			Arbol temp = nodos[j];
			nodos[j] = nodos[j + 1];
			nodos[j + 1] = temp;
		}
	}
	Arbol retArbol = nodos[numNodos - 1];
	return retArbol;
}

void printBinary(uint8_t *num, int bits) {
    for (int i = 0; i < bits; i++) {
        printf("%d", num[i]);
    }
}

Code *Obtener_Tabla(Arbol A, int numLeafs)
{
	Code *retCode = malloc(numLeafs * sizeof(*retCode));
	int cont = 0;
	HuffmanCode aux = {.length = 0, .num = NULL};
	Obtener_Valor(A, &cont, aux, retCode);
	return retCode;
}

void printTable(Code *table, int size)
{
	for (int i = 0; i < size; i++) {
		if (isprint(table[i].c)) {
			printf("'%c' -\t", table[i].c);
		} else {
			printf("%d -\t", table[i].c);
		}
		printBinary(table[i].h.num, table[i].h.length);
		printf("\n");
	}
}

void Obtener_Valor(Arbol A, int *cont, HuffmanCode h, Code *table)
{
	if (Es_Hoja(A)) {
		table[*cont].c = A->c;
		table[*cont].h = h;
		(*cont)++;
		return;
	}
	HuffmanCode leftAux;
	leftAux.length = h.length + 1;
	leftAux.num = malloc(leftAux.length * sizeof(*leftAux.num));
	for (int i = 0; i < h.length; i++) { // Copiamos los valores
		leftAux.num[i] = h.num[i];
	}
	leftAux.num[leftAux.length - 1] = 0;
	Obtener_Valor(A->izq, cont, leftAux, table);

	HuffmanCode rightAux;
	rightAux.length = h.length + 1;
	rightAux.num = malloc(rightAux.length * sizeof(*rightAux.num));
	for (int i = 0; i < h.length; i++) { // Copiamos los valores
		rightAux.num[i] = h.num[i];
	}
	rightAux.num[rightAux.length - 1] = 1;
	Obtener_Valor(A->der, cont, rightAux, table);
}