/**
 * @file huffman.h
 * 
 * @brief Encabezado con la defincion de arbol de huffman, codigos de huffman y tablas de frecuencias y sus funciones
 * 
 */
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>

/**
 * @struct Nodo
 * @brief Nodo de un arbol
 * 
 * Este nodo forma parte de un arbol.
 * Si ambos arboles dentro del nodo apuntan a NULL se considera un nodo hoja,
 * si no es un nodo intermediario y en ese caso el caracter no importa
 */
struct Nodo{
	struct Nodo *izq; //< Arbol izquierdo. debe tener una frecuencia menor o igual al derecho
	struct Nodo *der; //< Arbol derecho, debe tener una frecuencia mayor o igual al izquierdo
	uint8_t c; //< Byte, solo importante si el nodo es hoja
	uint32_t f; //< Si el nodo es hoja, la frecuencia, si no es hoja es la suma de frecuencias del arbol izq y der
};

/**
 * @typedef Arbol
 * @brief Un arbol es un apuntador a un nodo
 */
typedef struct Nodo* Arbol;

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
Arbol Crear_Nodo(uint8_t c, int f);

/**
 * @brief Identifica si un arbol es una hoja
 * 
 * @param A Arbol a analizar
 * 
 * @return Verdadero si es hoja, falso si no
 */
bool Es_Hoja(Arbol A);

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
Arbol Comb_Arbol(Arbol A, Arbol B);

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
Arbol Construir_Arbol(Arbol *nodos, int numNodos);

/**
 * @struct HuffmanCode
 * @brief Representa un codigo huffman como una secuencia de bits
 */
typedef struct {
	uint8_t *num; //< Apuntador al arreglo que contiene los bits del codigo huffman
	uint8_t length; //< El numero de bits del codigo de huffman
} HuffmanCode;

/**
 * @struct Code
 * @brief Asocia un byte con su codigo Huffman
 */
typedef struct {
	uint8_t c; //< Byte a codificar
	HuffmanCode h; //< El codigo Huffman correspondiente al byte
} Code;

/**
 * @brief Imprime un arreglo de uint8 como bits
 * 
 * @param num Apuntador al arreglo que representa una cadena de bits
 * @param bits Numero de bits en el arreglo
 * 
 * @note FOR DEBUGGING PURPOSES
 */
void printBinary(uint8_t *num, int bits);

/**
 * @brief Obtiene la tabla de bytes y sus codigos Huffman a partir de un arbol
 * 
 * @param A Arbol con los bytes y sus frecuencias
 * @param num Numero de bytes en el arbol
 * 
 * @return Arreglo de struct Code, contiene los bytes y sus codigos Huffman
 */
Code *Obtener_Tabla(Arbol A, int num);

/**
 * @brief Imprime la tabla de bytes y sus codigos huffman
 * 
 * @param table Arreglo de bytes y codigos huffman
 * @param size Numero de bytes en la tabla
 * 
 * @note FOR DEBUGGING PURPOSES
 */
void printTable(Code *table, int size);

#endif