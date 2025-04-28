/**
 * @file binary.c
 * 
 * @brief Implementacion de funciones en binary.h
 * 
 */
#include "binary.h"

#include <stdio.h>

/**
 * @brief Inserta un bit en la posicion menos significativa.
 * 
 * @param num Entero de 8 bits sin signo
 * @param bit Bit a insertar
 * 
 * @return Entero de 8 bits modificado
 */
uint8_t push_bin(uint8_t num, int bit)
{
	// Shifteamos los bits 1 a la izquierda
	num = num << 1;
	// Añadimos el bit
	num += bit;
	return num;
}

/**
 * @brief Obtiene el bit en una posicion dada.
 * 
 * @param num Entero de 8 bits sin signo
 * @param pos Posicion del bit a buscar
 * 
 * @return Valor del bit en la posicion dada
 */
int get_bit(uint8_t num, int pos)
{
	// Movemos el 1 en la mascara a la posicion deseada
	uint8_t mask = 1 << pos;
	return num & mask;
}

/**
 * @brief Imprime un entero de 8 bits sin signo en representacion binaria.
 * 
 * @param value Entero de 8 bits sin signo
 * 
 * @note FOR DEBUGGING PURPOSES
 */
void print_uint8_b(uint8_t value) {
	for (int i = 7; i >= 0; i--) {
		printf("%c", (value & (1 << i)) ? '1' : '0');
	}
	printf(" ");
}