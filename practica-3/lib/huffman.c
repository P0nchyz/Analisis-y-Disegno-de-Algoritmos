/**
 * @file huffman.c
 * 
 * @brief Implementación de las funciones en huffman.h
 * 
 */
#include <ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "huffman.h"

void Obtener_Valor(Arbol A, int *cont, HuffmanCode h, Code *table);

/**
 * @brief Crea un nuevo nodo con el byte y frequencia dadas.
 * 
 * La funcion aloja memoria para un nuevo nodo. establece el byte y frecuencia
 * e inicializa los arboles izquierda y derecha a NULL
 * 
 * @param c El byte a guardar en el nodo
 * @param f La frecuencia asociada al byte
 * 
 * @return El apuntador al nodo (Arbol) creado
 * 
 * @note El usuario es responsable de liberar la memorai alojada
 */
Arbol Crear_Nodo(uint8_t c, int f)
{
	Arbol retArbol= malloc(sizeof(struct Nodo));
	retArbol->c = c;
	retArbol->f = f;
	retArbol->izq = retArbol->der = NULL;
	
	return retArbol;
}

/**
 * @brief Identifica si un arbol es una hoja
 * 
 * @param A Arbol a analizar
 * 
 * @return Verdadero si es hoja, falso si no
 */
bool Es_Hoja(Arbol A)
{
	if (A->der == NULL || A->izq == NULL)
		return true;
	else
		return false;
}

/**
 * @brief Combina dos arboles en uno solo
 * 
 * Esta funcion combina dos arboles en uno solo, la raiz de este nuevo arbol
 * contiene la suma de las frecuencias de ambos arboles.
 * 
 * El arbol con la menor frecuencia se coloco en la izquierda y el otro en la derecha
 * 
 * @param A Arbol a combinar
 * @param B Arbol a combinar
 * 
 * @return Arbol combinado
 */
Arbol Comb_Arbol(Arbol A, Arbol B)
{
	Arbol retArbol= malloc(sizeof(struct Nodo)); 
	retArbol->f = A->f + B->f;
	retArbol->izq = (A->f >= B->f) ? B : A; // Si A > B guardamos B, si no A
	retArbol->der = (A->f < B->f) ? B : A; // Si A > B guardamos A, si no B
	return retArbol;
}

/**
 * @brief Combina todos los Arboles en un arreglo
 * 
 * @param nodos Arreglo de Arboles a combinar
 * @param numNodos Numero de Arboles a combinar
 * 
 * @return El Arbol resultante de combinar todos los arboles del arreglo
 * 
 * @note Esta funcion modifica el arreglo de Arboles, se espera que este no se vuelva a utilizar
 */
Arbol Construir_Arbol(Arbol *nodos, int numNodos)
{
	// Combinamos los Arboles en el arreglo de dos en dos
	for (int i = 0; i < numNodos - 1; i++) {
		// Guardamos la combinacion de ambos arboles en la posicion del mayor
		nodos[i + 1] = Comb_Arbol(nodos[i], nodos[i + 1]);
		// Colocamos el arbol en la posicion correcta dentro del arreglo de acuerdo a su frecuencia
		for (int j = i + 1; j < numNodos - 1; j++) {
			// Si la frecuencia del arbol es menor que la del siguiente salimos del loop
			if (nodos[j]->f < nodos[j + 1]->f)
				break;
			// Si la frecuencia es mayor o igual lo intercambiamos
			Arbol temp = nodos[j];
			nodos[j] = nodos[j + 1];
			nodos[j + 1] = temp;
		}
	}
	// El arbol final se encuentra en la posicion final del arreglo
	Arbol retArbol = nodos[numNodos - 1];
	return retArbol;
}

/**
 * @brief Imprime un arreglo de uint8 como bits
 * 
 * @param num Apuntador al arreglo que representa una cadena de bits
 * @param bits Numero de bits en el arreglo
 * 
 * @note FOR DEBUGGING PURPOSES
 */
void printBinary(uint8_t *num, int bits) {
    for (int i = 0; i < bits; i++) {
        printf("%d", num[i]);
    }
}

/**
 * @brief Obtiene la tabla de bytes y sus codigos Huffman a partir de un arbol
 * 
 * @param A Arbol con los bytes y sus frecuencias
 * @param num Numero de bytes en el arbol
 * 
 * @return Arreglo de struct Code, contiene los bytes y sus codigos Huffman
 */
Code *Obtener_Tabla(Arbol A, int numLeafs)
{
	Code *retCode = malloc(numLeafs * sizeof(*retCode)); //< Alojamos la memoria necesaria para la tabla
	int cont = 0; //< Inicializamos el contador para la funcion de Obterner_Valor
	HuffmanCode aux = {.length = 0, .num = NULL}; //< Codigo huffman inicial
	// Obtenemos los codigos huffman para todos los bytes del arbol
	Obtener_Valor(A, &cont, aux, retCode);
	return retCode;
}

/**
 * @brief Imprime la tabla de bytes y sus codigos huffman
 * 
 * @param table Arreglo de bytes y codigos huffman
 * @param size Numero de bytes en la tabla
 * 
 * @note FOR DEBUGGING PURPOSES
 */
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

/**
 * @brief Llena la tabla de bytes y codigos huffman
 * 
 * @param A Arbol con los bytes y sus frecuencias
 * @param cont Referencia al contador del numero de elementos en la tabla
 * @param h Codigo huffman acumulado con el recorrido del arbol
 * @param table Arreglo en el que guardar los bytes y codigos huffman
 */
void Obtener_Valor(Arbol A, int *cont, HuffmanCode h, Code *table)
{
	// Si el arbol es una hoja hemos llegado ya a un byte
	if (Es_Hoja(A)) {
		// Nos posicionamos en el espacio de la tabla correspondiente
		table[*cont].c = A->c;
		table[*cont].h = h;
		// Aumentamos el contador
		(*cont)++;
		return;
	}

	// Si no es hoja recorremos a la izquierda
	HuffmanCode leftAux;
	leftAux.length = h.length + 1; // El codigo huffman aumenta en tamaño
	leftAux.num = malloc(leftAux.length * sizeof(*leftAux.num)); // Alojamos memoria para el arreglo de bits
	for (int i = 0; i < h.length; i++) { // Copiamos los valores
		leftAux.num[i] = h.num[i];
	}
	leftAux.num[leftAux.length - 1] = 0; // Como vamos a la izquierda el ultimo bit es 0
	Obtener_Valor(A->izq, cont, leftAux, table);

	// Recorremos a la derecha
	HuffmanCode rightAux;
	rightAux.length = h.length + 1; // El codigo huffman aumenta en tamaño
	rightAux.num = malloc(rightAux.length * sizeof(*rightAux.num)); // Alojamos memoria para el arreglo de bits
	for (int i = 0; i < h.length; i++) { // Copiamos los valores
		rightAux.num[i] = h.num[i];
	}
	rightAux.num[rightAux.length - 1] = 1; // Como vamos a la derecha el ultimo bit es 1
	Obtener_Valor(A->der, cont, rightAux, table);
}