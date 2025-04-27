#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>

struct Nodo{
	struct  Nodo *izq;
	struct Nodo *der;
	uint8_t c;
	uint32_t f;
};
typedef struct Nodo* Arbol;

Arbol Crear_Nodo(uint8_t c, int f);

bool Es_Hoja(Arbol A);

Arbol Comb_Arbol(Arbol A, Arbol B);

Arbol Construir_Arbol(Arbol *nodos, int numNodos);

typedef struct {
	uint8_t *num;
	uint8_t length;
} HuffmanCode;

typedef struct {
	uint8_t c;
	HuffmanCode h;
} Code;

void printBinary(uint8_t *num, int bits);


Code *Obtener_Tabla(Arbol A, int num);

void printTable(Code *table, int size);

#endif