#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/sort.h"
#include "lib/tiempo.h"

enum SortingAlgorithm {BUBBLE, BUBBLE1, BUBBLE2, INSERTION, SELECTION, SHELL, TREE, MERGE, QUICK, HEAP};

typedef void (*sorting_function)(int *array, unsigned int size);

void printUsage(char *programName);

int getSortingAlgorithm(char *option);

sorting_function selectSortingAlgorithm(enum SortingAlgorithm option);

int main(int argc, char *argv[])
{
	enum SortingAlgorithm selectedAlgorithm;
	int size;
	if (4 != argc){
		printUsage(argv[0]);
		exit(1);
	} else {
		size = atoi(argv[1]);
		if (0 != strcmp(argv[2], "-a")) {
			printf("ERROR: Unknown argument %s.\n\n", argv[2]);
			printUsage(argv[0]);
			exit(1);
		}
		selectedAlgorithm = getSortingAlgorithm(argv[3]);
		if (-1 == selectedAlgorithm) {
			printf("ERROR: Unknown algorithm option %s.\n\n", argv[3]);
			printUsage(argv[0]);
			exit(1);
		}
	}

	sorting_function sort = selectSortingAlgorithm(selectedAlgorithm);
	int *array = malloc(size * sizeof(*array));
	for (int i = 0; i < size; i++)
		scanf("%d", &array[i]);

	double utime0, stime0, wtime0, utime1, stime1, wtime1;

	uswtime(&utime0, &stime0, &wtime0);

	sort(array, size);

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