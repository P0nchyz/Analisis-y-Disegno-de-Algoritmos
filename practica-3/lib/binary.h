/**
 * @file binary.h
 * 
 * @brief Encabezado con la defincion de funciones para el manejo de bits en uint8.
 * 
 */
#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>

/**
 * @brief Inserta un bit en la posicion menos significativa.
 * 
 * @param num Entero de 8 bits sin signo
 * @param bit Bit a insertar
 * 
 * @return Entero de 8 bits modificado
 */
uint8_t push_bin(uint8_t num, int bit);

/**
 * @brief Obtiene el bit en una posicion dada.
 * 
 * @param num Entero de 8 bits sin signo
 * @param pos Posicion del bit a buscar
 * 
 * @return Valor del bit en la posicion dada
 */
int get_bit(uint8_t num, int pos);

/**
 * @brief Imprime un entero de 8 bits sin signo en representacion binaria.
 * 
 * @param value Entero de 8 bits sin signo
 * 
 * @note FOR DEBUGGING PURPOSES
 */
void print_uint8_b(uint8_t value);

#endif