/*
Autores:
Bautista Quijano Anayeli
Garcia Morlan Julio Amauri
Hernandez Zamora Valeria (Huevos Val)
Jimenez Rodriguez Alan Gael (HUevos Gael ojala te atropelle un burro)
Vergara Gamboa Jose Alfonso 

VERSION: 1.0

Descripcion:
Este es un programa que sirve de comparador de algoritmos de ordenamiento que 
mide y compara los tiempos de ejecucion de cada uno.

Beskrivning:
Detta är ett program som fungerar som en jämförare av sorteringsalgoritmer 
och som mäter och jämför körtiderna för varje algoritm.

Compilacion: 
gcc -o sort.out main.c lib/tiempo.c lib/sorting/bubble.c lib/sorting/heap.c lib/sorting/insertion.c lib/sorting/merge.c lib/sorting/quick.c lib/sorting/selection.c lib/sorting/shell.c lib/sorting/tree.c
HUEVOS JOSE.c
Ejecucion: main.exe

*/

//Librerias 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/sort.h"
#include "lib/tiempo.h"

/*
enum SortingAlgorithm: Define un enumerador para asignar nombres a las constantes, los cuales representan
los nombres de los algoritmos disponibles dentro del programa.
Cada valor corresponde a:
Una opcion de en la linea de comandos.
Una funcion para especificar el algoritmo de ordenamiento.
*/
enum SortingAlgorithm {BUBBLE, BUBBLE1, BUBBLE2, INSERTION, SELECTION, SHELL, TREE, MERGE, QUICK, HEAP};

//Definicion de un tipo de puntero a funcion.
typedef void (*sorting_function)(int *array, unsigned int size);

/*
Funcion Void (Recuerda que las funciones void no retornan ningun valor)
Prametros que recibe:
char *programName 
*/
void printUsage(char *programName);

/*
Declaracion de la funcion getSorting
Recibe 
char *option
Retorna
Valor entero representando la opcion correspondiente asignada en 
enum SortingAlgorithm 
*/
int getSortingAlgorithm(char *option);

/*
Declara la funcion sorting_function selectSortingAlgorithm
Obtiene la funcion de ordenamiento asociado a un algoritmo.
Reciobe 
enum selectSortingAlgorithm  option
Retorna 
sorting_function (Sieendo este puntero a la funcion de ordenamiento correspondiente)
*/
sorting_function selectSortingAlgorithm(enum SortingAlgorithm option);

int main(int argc, char *argv[])
{
	//Declaracion de la variable que almacenara el algoritmo de ordenamiento
	enum SortingAlgorithm selectedAlgorithm;
	//Declaracion de la variable para almacenar el tamanio del arreglo
	//Usare ni en lugar de ñ, para que no haya caracteres raros
	int size;
	/*
 	Validacion para el numero de argumentos daados al programa 
 	*/
	if (4 != argc){
		printUsage(argv[0]);
		exit(1);
	} 
	/*
 	Se asigna a size el valor numerico del priumer argumento usando atoi.
  	Verifica que el segundo argumento sea exactamente "-a" para especificar
   	el algoritmo a usar, de lo contrario marcara error 
 	*/
	else {
		size = atoi(argv[1]);
		if (0 != strcmp(argv[2], "-a")) {
			printf("ERROR: Unknown argument %s.\n\n", argv[2]);
			printUsage(argv[0]);
			exit(1);
		}
		/*
  		Determina el algoritmo de ordenamiento a usar en el programa
  		*/
		selectedAlgorithm = getSortingAlgorithm(argv[3]);
		/*
  		De no cumplirse la condicion (algoritmo seleccionado por el usuario es 
    		invalido) saltara un mensaje de error.
  		*/
		if (-1 == selectedAlgorithm) {
			printf("ERROR: Unknown algorithm option %s.\n\n", argv[3]);
			printUsage(argv[0]);
			exit(1);
		}
	}

	/*
 	selectSortingAlgorithm recibe el valor de enum y retorna 
  	el puntero a la funcion correspondiente (sort servira para 
   	llamar al algoritmo seleccionado)
    	
     	int *array = malloc(size * sizeof(*array)): Reserva memoria para
        el arreglo (malloc para memoria dinamica, sizeof calcula el tamanio 
	de un entero, array es un puntero a un bloque de memoria para almacenar
 	los size numeros)	

  	scanf: Lee los enteros desde la entrada estandar, los guarda en la posicion de i
 	*/
	sorting_function sort = selectSortingAlgorithm(selectedAlgorithm);
	int *array = malloc(size * sizeof(*array));
	for (int i = 0; i < size; i++)
		scanf("%d", &array[i]);

	//Variables para los tiempos de ejecucion
	double utime0, stime0, wtime0, utime1, stime1, wtime1;

	//Registro de los tiempos iniciales (Antes del ordenamiento)
	uswtime(&utime0, &stime0, &wtime0);

	//Ejecuciion del algoritmo seleccionado (Sort es el apuntador a funcion)
	sort(array, size);

	//Registro de los tiempos finales (Ya ordenados)
	uswtime(&utime1, &stime1, &wtime1);

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

	FILE *outFile = fopen("out.txt", "w");
	for (int i = 0; i < size; i++) {
		fprintf(outFile, "%d\n", array[i]);
	}
	fclose(outFile);
	return 0;
}

void printUsage(char *programName)
{
	printf("Usage:\n");
	printf("\t%s <size> -a <algorithm>\n", programName);
	printf("\nList of Algorithms\n");
	printf("\tB\tBubble Sort\n");
	printf("\tB1\tOptimized Bubble Sort 1\n");
	printf("\tB2\tOptimized Bubble Sort 2\n");
	printf("\tI\tInsertion Sort\n");
	printf("\tS\tSelection Sort\n");
	printf("\tSH\tShell Sort\n");
	printf("\tT\tTree Sort\n");
	printf("\tM\tMerge Sort\n");
	printf("\tQ\tQuick Sort\n");
	printf("\tH\tHeap Sort\n");
}

int getSortingAlgorithm(char *option)
{
	if (0 == strcmp(option, "B")) return BUBBLE;
	if (0 == strcmp(option, "B1")) return BUBBLE1;
	if (0 == strcmp(option, "B2")) return BUBBLE2;
	if (0 == strcmp(option, "I")) return INSERTION;
	if (0 == strcmp(option, "S")) return SELECTION;
	if (0 == strcmp(option, "SH")) return SHELL;
	if (0 == strcmp(option, "T")) return TREE;
	if (0 == strcmp(option, "M")) return MERGE;
	if (0 == strcmp(option, "Q")) return QUICK;
	if (0 == strcmp(option, "H")) return HEAP;
	return -1;
}

sorting_function selectSortingAlgorithm(enum SortingAlgorithm option)
{
	sorting_function r_func;
	switch (option)
	{
	case BUBBLE:
		r_func = bubble_sort;
		break;
	case BUBBLE1:
		r_func = optimized_bubble_sort_1;
		break;
	case BUBBLE2:
		r_func = optimized_bubble_sort_2;
		break;
	case INSERTION:
		r_func = insertion_sort;
		break;
	case SELECTION:
		r_func = selection_sort;
		break;
	case SHELL:
		r_func = shell_sort;
		break;
	case TREE:
		r_func = tree_sort;
		break;
	case MERGE:
		r_func = merge_sort;
		break;
	case QUICK:
		r_func = quick_sort;
		break;
	case HEAP:
		r_func = heap_sort;
		break;
	default:
		r_func = NULL;
		break;
	}
	return r_func;
}
