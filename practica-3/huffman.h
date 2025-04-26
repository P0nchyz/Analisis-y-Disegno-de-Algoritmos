#ifndef HUFFMAN_H
#define HUFFMAN_H

struct Nodo{
	struct  Nodo * izq;
	struct Nodo * der;
	unsigned char c;
	int f;
};
typedef struct Nodo* Arbol;

Arbol Crear_Nodo(unsigned char c, int f);

Arbol Comb_Arbol(Arbol A, Arbol B);



typedef struct {
	unsigned char *num;
	unsigned char length;
} HuffmanCode;

typedef struct {
	unsigned char c;
	HuffmanCode h;
} Code;

void printBinary(unsigned char *num, int bits);


Code *Obtener_Tabla(Arbol A, int num);

#endif