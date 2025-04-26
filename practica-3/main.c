#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "huffman.h"

Arbol *get_frequencies(FILE *file, bool isExplicit, int *size);
void quick_sort(Arbol *array, unsigned int size);

void compressFile(char *fileName);
void uncompressFile(char *fileName, char *freqFile);


int main(int argc, char *argv[])
{
	if (argc == 2) {
		compressFile(argv[1]);
	} else if (argc == 3) {
		uncompressFile(argv[1], argv[2]);
	} else {
		printf("BAD ARGUMENTS.\n");
		exit(1);
	}
}

void compressFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	if(file == NULL) {
		printf("Error: No se pudo abrir el archivo\n\n");
		exit(1);
	}
	int sizeNodos;
	Arbol *nodos = get_frequencies(file, false, &sizeNodos);

	FILE *freqFile = fopen("frequencias.txt", "w");
	for (int i = 0; i < sizeNodos; i++) {
		fprintf(freqFile, "\"%d\"--%d\n", nodos[i]->c, nodos[i]->f);
	}
	fclose(freqFile);

	for (int i = 0; i < sizeNodos - 1; i++) {
		nodos[i + 1] = Comb_Arbol(nodos[i], nodos[i + 1]);
		for (int j = i + 1; j < sizeNodos - 1; j++) {
			if (nodos[j]->f < nodos[j + 1]->f)
				break;
			Arbol temp = nodos[j];
			nodos[j] = nodos[j + 1];
			nodos[j + 1] = temp;
		}
	}
	Arbol finalTree = nodos[sizeNodos - 1];

	Code *table = Obtener_Tabla(finalTree, sizeNodos);

	FILE *newFile = fopen("codificacion.dat", "w");
	unsigned char buffer;
	rewind(file);
	unsigned char out = 0;
	int bitsPacked = 0;
	while (fread(&buffer, sizeof(char), 1, file))
	{
		int tableIndex = 0;
		for (int i = 0; i < sizeNodos; i++) {
			if (buffer == table[i].c) {
				tableIndex = i;
				break;
			}
		}
		HuffmanCode currentCode = table[tableIndex].h;
		for (int i = 0; i < currentCode.length; i++) {
			if (bitsPacked < 7) {
				out += currentCode.num[i];
				out = out << 1;
				bitsPacked++;
			} else if (bitsPacked == 7) {
				out += currentCode.num[i];
				bitsPacked = 0;
				fwrite(&out, sizeof(char), 1, newFile);
				out = 0;
			}
		}
	}
	out = out << (7 - bitsPacked);
	fwrite(&out, sizeof(char), 1, newFile);
	fclose(newFile);
}

void uncompressFile(char *fileName, char *freqFile)
{
	exit(1);
}


Arbol *get_frequencies(FILE *file, bool isExplicit, int *size)
{
	Arbol *frequency = malloc(256 * sizeof(*frequency));
	if (isExplicit) {
		printf("POR IMPLEMENTAR\n");
		exit(1);
	}
	for (int i = 0; i < 256; i++) {
		frequency[i] = Crear_Nodo(i, 0);
	}
	unsigned char buffer;
	while (fread(&buffer, sizeof(char), 1, file) == 1)
	{
		frequency[buffer]->f++;
	}
	quick_sort(frequency, 256);
	int nonZeroItems = 256;
	for (int i = 0; i < 256; i++) {
		if (frequency[i]->f == 0) {
			nonZeroItems--;
			free(frequency[i]);
			frequency[i] = NULL;
			continue;
		}
		*size = nonZeroItems;
		return &(frequency[i]);
	}
}



int findPivot(Arbol *array, int size)
{
	// Selecciona el ultimo elemento como pivote
	int pivot = array[size - 1]->f;
	// Indice comienza fuera del arreglo
	int i = -1;
	// Recorre todos los elementos del arreglo menos el ultimo (pivote)
	for (int j = 0; j < size - 1; j++) {
		// Si el elemento en el indice j es menor que el pivote se intercambia con el elemento en i
		// el elemento en i corresponde al elemento mas pequeño
		if (array[j]->f < pivot) {
			i++;
			Arbol temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	// Se incrementa i para obtener la posicion del pivote y se intercambia a su posicion final
	i++;
	Arbol temp = array[i];
	array[i] = array[size - 1];
	array[size - 1] = temp;
	return i;
}

void quick_sort(Arbol *array, unsigned int size)
{
	if (size <= 1)
		return;
	
	int pivot = findPivot(array, size);
	// leftArray es una referencia al principio del array
	Arbol *leftArray = array;
	// poniendo el tamaño como el valor de pivot nos aseguramos que el array acabe uno antes del pivote
	unsigned int leftSize = pivot;
	quick_sort(leftArray, leftSize);
	// rightArray es una referencia a el elemento despues del pivote
	Arbol *rightArray = array + pivot + 1;
	unsigned int rightSize = size - (leftSize + 1);
	quick_sort(rightArray, rightSize);

	return;
}