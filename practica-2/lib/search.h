/**
 * @file search.h
 * 
 * @brief Encabezado con la defincion de las funciones de los distintos algoritmos de busqueda
 * 
 */
#ifndef SEARCH_H
#define SEARCH_H

/**
 * @brief Busqueda Lineal
 * 
 * Checa los elementos del arreglo uno a uno hasta encontrar el deseado.
 * 
 * O(n)
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int linear_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda Binaria
 * 
 * Divide de manera repetida el intervalo de busqueda a la mitad, hasta
 * que el valor 'target' sea encontrado, o el intervalo este vacio
 * 
 * O(log n)
 * 
 * @param array Apuntador al arreglo de enteros ordenados en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 * 
 * @note Requiere un arreglo ordenado
 */
int binary_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda con arbol binario de busqueda (BST)
 * 
 * Construye un arbol binario de busqueda con el arreglo de entrada,
 * y busca el 'target' traversando el arbol
 * 
 * Promedio: O(log n)
 * Peor: O(n)
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int binary_tree_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda Exponencial
 * 
 * 
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 *
 * @note Requiere un arreglo ordenado
 */
int exponential_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda Fibonacci
 * 
 * 
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int fibonacci_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda Lineal con Hilos
 * 
 * 
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int thread_linear_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda Binaria con Hilos
 * 
 * 
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int thread_binary_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda con Arbol Binaria con Hilos
 * 
 * 
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int thread_binary_tree_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda Exponencial con Hiloa
 * 
 * 
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int thread_exponential_search(int *array, unsigned int size, int target);

/**
 * @brief Busqueda Fibonacci con Hilos
 * 
 * 
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
int thread_fibonacci_search(int *array, unsigned int size, int target);

#endif