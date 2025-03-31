#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/search.h"
#include "lib/tiempo.h"

enum SearchingAlgorithms {LINEAR, BINARY, BINARY_TREE, EXPONENTIAL, FIBONACCI, LINEAR_T, BINARY_T, BINARY_TREE_T, EXPONENTIAL_T, FIBONACCI_T};

typedef int (*searching_function) (int *array, unsigned int size, int target);

void printUsage(char *programName);

int getSearchingAlgorithm(char *option, bool isUsingThreads);

searching_function selectSearchingAlgorithm(enum SearchingAlgorithms option);

int main(int argc, char *argv[])
{
	enum SearchingAlgorithms selectedAlgorithm;
	int target;
	unsigned int size;
	
	if (argc != 6) {
		printUsage(argv[0]);
		exit(1);
	} else {
		target = atoi(argv[1]);
		if (strcmp(argv[2], "-s") != 0) {
			printf("ERROR: Unknown argument %s.\n\n", argv[2]);
			printUsage(argv[0]);
			exit(1);
		}
		size = atoi(argv[3]);
		if (strcmp(argv[4], "-at") == 0) {
			selectedAlgorithm = getSearchingAlgorithm(argv[5], true);
		} else if (strcmp(argv[4], "-a") == 0) {
			selectedAlgorithm = getSearchingAlgorithm(argv[5], false);
		} else {
			printf("ERROR: Unknown argument %s.\n\n", argv[4]);
			printUsage(argv[0]);
			exit(1);
		}
		if (selectedAlgorithm == -1) {
			printf("ERROR: Unknown algorithm option %s.\n\n", argv[5]);
			printUsage(argv[0]);
			exit(1);
		}
	}

	searching_function search = selectSearchingAlgorithm(selectedAlgorithm);
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
	} else {
		if (strcmp(option, "L") == 0) return LINEAR;
		if (strcmp(option, "B") == 0) return BINARY;
		if (strcmp(option, "T") == 0) return BINARY_TREE;
		if (strcmp(option, "E") == 0) return EXPONENTIAL;
		if (strcmp(option, "F") == 0) return FIBONACCI;
		return -1;
	}
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