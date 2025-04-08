/**
 * @file main.c
 * 
 * @author Bautista Quijano Anayeli
 * @author Garcia Morlan Julio Amauri
 * @author Jimenez Rodriguez Alan Gael Gael
 * @author Hernandez Zamora Valeria
 * @author Vergara Gamboa José Alfonso
 * 
 * @date Apr-2025
 * 
 * @version 1.0.0
 * 
 * Descripción:
 * El programa tiene como función comparar diversos algoritmos de busqueda,
 * tanto single-threaded como multi-threaded,
 * por lo que mide el tiempo que tardan en procesar y lo devuelve al usuario.
 * 
 * El número de hilos a usar en la implementación multithreaded de cada algoritmo
 * esta hardcodiado, pero puede ser facilmente remplazable por un argumento.
 * 
 * Compilación:
 * 	make
 * Ejecución ./sort.out
 * 
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/search.h"
#include "lib/tiempo.h"

/**
 * @enum SearchingAlgorithms
 * @brief Enumera varios tipos de algoritmos de busqueda, incluyendo sus versiones estandard y multi-threaded
 * 
 * Este enum define un conjunto de algoritmos de busqueda que pueden ser usados para buscar elementos
 * dentro de un arreglo. Las variantes con el sufijo '_T' indican versiones multi-threaded, las cuales
 * utilizan multiples hilos para distrubuir la workload
 */
enum SearchingAlgorithms {LINEAR, BINARY, BINARY_TREE, EXPONENTIAL, FIBONACCI, LINEAR_T, BINARY_T, BINARY_TREE_T, EXPONENTIAL_T, FIBONACCI_T};

/**
 * @typedef searching_function
 * @brief Apuntador de funcion para algoritmo de ordenamiento.
 * 
 * Esta typedef define un apuntador para algoritmos de ordenamiento que operan
 * en arreglos de enteros.
 * 
 * @param array Apuntador al arreglo de enteros en el que buscar.
 * @param size El numero de elementos en el arreglo
 * @param target El valor del entero a buscar en el arreglo
 * 
 * @return El index del numero target en el arreglo si se encontro, -1 en caso contrario
 */
typedef int (*searching_function) (int *array, unsigned int size, int target);

/**
 * @brief Imprime las instrucciones de uso para el programa.
 * 
 * Esta funcion muestra una guia para usar el programa desde la terminal,
 * incluyendo los argumentos necesarios y una lista de los algoritmos disponibles,
 * con sus codigos correspondientes.
 * 
 * @param programName El nombre del archivo ejecutable, normalemente pasado al programa como 'argv[0]' desde 'main'
 */
void printUsage(char *programName);

/**
 * @brief Recupera el valor correspondiente del enum de algoritmos de busqueda de acuerdo a 'option'
 * 
 * La funcion mapea una cadena que representa a un algoritmo de busqueda. La funcion utiliza el bool 'isUsingThreads'
 * para determinar si debe regresar la version estandard o multi-threaded.
 * 
 * @param option Una cadena representando un algoritmo de busqueda
 * @param isUsingThreads Bandera booleana que indica si el algoritmo es multi-threaded
 * 
 * @return El correspondiente valor del enum de algoritmos, o '-1' si la opciob es invalida
 */
int getSearchingAlgorithm(char *option, bool isUsingThreads);

/**
 * @brief Selecciona un algoritmo de busqueda de acuerda a la opcion dada.
 * 
 * La funcion toma una de las opciones del enum 'searchingAlgorihtms' y
 * retorna el apuntador a la funcion de busqueda correspondiente.
 * 
 * @param option El algoritmo de busqueda seleccionado.
 * 
 * @return Un apuntador a la funcion de busqueda basada en 'option', o 'NULL' si no se proporciona una opcion valida.
 * 
 * @note El apuntador que regresa esta funcion puede ser usado para invocar el algoritmo de busqueda correspondiente.
 */
searching_function selectSearchingAlgorithm(enum SearchingAlgorithms option);

int main(int argc, char *argv[])
{
	// Declaracion de variables
	enum SearchingAlgorithms selectedAlgorithm; ///< Guarda el algoritmo seleccionado
	unsigned int size; ///< Tamaño del arreglo
	int target; ///< El valor a buscar
	
	// Checa si el numero de argumentos es correcto
	if (argc != 6) {
		printUsage(argv[0]);
		exit(1);
	} else {
		// Obtiene el valor a buscar
		target = atoi(argv[1]); ///< Convierte el primer argumento a un entero

		// Probamos si el segundo argumento es el esperado '-s'
		if (strcmp(argv[2], "-s") != 0) {
			printf("ERROR: Unknown argument %s.\n\n", argv[2]);
			printUsage(argv[0]);
			exit(1);
		}

		// Obtenemos el tamaño del argumento
		size = atoi(argv[3]); ///< Convierte el tercer argumento a un entero

		// Checa el argumento de seleccion de algoritmo
		if (strcmp(argv[4], "-at") == 0) {
			selectedAlgorithm = getSearchingAlgorithm(argv[5], true); //< Selecciona algortmos threaded
		} else if (strcmp(argv[4], "-a") == 0) {
			selectedAlgorithm = getSearchingAlgorithm(argv[5], false); //< Selecciona algoritmos estandar
		} else {
			printf("ERROR: Unknown argument %s.\n\n", argv[4]);
			printUsage(argv[0]);
			exit(1);
		}

		// Valida el algoritmo seleccionado
		if (selectedAlgorithm == -1) {
			printf("ERROR: Unknown algorithm option %s.\n\n", argv[5]);
			printUsage(argv[0]);
			exit(1);
		}
	}

	// Selecciona la funcion de busqueda basada en la opcion seleccionada
	searching_function search = selectSearchingAlgorithm(selectedAlgorithm);

	// Alojamos memoria para el arreglo
	int *array = malloc(size * sizeof(*array));
	for (int i = 0; i < size; i++)
		scanf("%d", &array[i]);
	
	//Variables para los tiempos de ejecucion
	double utime0, stime0, wtime0, utime1, stime1, wtime1;

	//Registro de los tiempos iniciales (Antes del ordenamiento)
	uswtime(&utime0, &stime0, &wtime0);

	//Ejecuciion del algoritmo seleccionado (Sort es el apuntador a funcion)
	int index = search(array, size, target);

	//Registro de los tiempos finales (Ya ordenados)
	uswtime(&utime1, &stime1, &wtime1);

	if (index == -1)
		printf("Element %d was not found.\n\n", target);
	else
		printf("Element %d found at index: %d.\n\n", target, index);

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	return 0;
}

void printUsage(char *programName)
{
	printf("Usage:\n");
	printf("\t%s <target> -s <size> -a[t] <algorithm>\n\n", programName);
	printf("The [t] optional argument indicates the use of threads.\n\n");
	printf("List of Algorithms:\n");
	printf("\tL\tLinear Search\n");
	printf("\tB\tBinary Search\n");
	printf("\tT\tBinary Search Tree Search\n");
	printf("\tE\tExponential Search\n");
	printf("\tF\tFibonacci Search\n");
}

int getSearchingAlgorithm(char *option, bool isUsingThreads)
{
	if (isUsingThreads) {
		if (strcmp(option, "L") == 0) return LINEAR_T;
		if (strcmp(option, "B") == 0) return BINARY_T;
		if (strcmp(option, "T") == 0) return BINARY_TREE_T;
		if (strcmp(option, "E") == 0) return EXPONENTIAL_T;
		if (strcmp(option, "F") == 0) return FIBONACCI_T;
		return -1;
	}
	if (strcmp(option, "L") == 0) return LINEAR;
	if (strcmp(option, "B") == 0) return BINARY;
	if (strcmp(option, "T") == 0) return BINARY_TREE;
	if (strcmp(option, "E") == 0) return EXPONENTIAL;
	if (strcmp(option, "F") == 0) return FIBONACCI;
	return -1;
}

searching_function selectSearchingAlgorithm(enum SearchingAlgorithms option)
{
	searching_function r_func;
	switch (option)
	{
	case LINEAR:
		r_func = linear_search;
		break;
	case BINARY:
		r_func = binary_search;
		break;
	case EXPONENTIAL:
		r_func = exponential_search;
		break;
	case FIBONACCI:
		r_func = fibonacci_search;
		break;
	case LINEAR_T:
		r_func = thread_linear_search;
		break;
	case BINARY_T:
		r_func = thread_binary_search;
		break;
	case EXPONENTIAL_T:
		r_func = thread_exponential_search;
		break;
	case FIBONACCI_T:
		r_func = thread_fibonacci_search;
		break;
	default:
		r_func = NULL;
		break;
	}
	return r_func;
}