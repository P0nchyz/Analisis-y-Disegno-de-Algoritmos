#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "binary.h"

Arbol *get_frequencies(FILE *file, bool isExplicit, int *size);
void quick_sort(Arbol *array, unsigned int size);

void compressFile(char *fileName);
void uncompressFile(char *fileName, char *freqFileName);


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
	if (file == NULL) {
		printf("Error: No se pudo abrir el archivo\n\n");
		exit(1);
	}
	int numNodos;
	Arbol *nodos = get_frequencies(file, false, &numNodos);

	FILE *freqFile = fopen("frequencias.txt", "w");
	for (int i = 0; i < numNodos; i++) {
		if (isprint(nodos[i]->c)) {
			fprintf(freqFile, "'%c'--%d\n", nodos[i]->c, nodos[i]->f);
		} else {
			fprintf(freqFile, "%d--%d\n", nodos[i]->c, nodos[i]->f);
		}
	}
	fclose(freqFile);

	Arbol finalTree = Construir_Arbol(nodos, numNodos);

	Code *table = Obtener_Tabla(finalTree, numNodos);
	printTable(table, numNodos);

	FILE *newFile = fopen("codificacion.dat", "w");
	uint8_t buffer;
	rewind(file);
	uint8_t out = 0;
	int bitsPacked = 0;
	while (fread(&buffer, sizeof(buffer), 1, file)) {
		int tableIndex = 0;
		for (int i = 0; i < numNodos; i++) {
			if (buffer == table[i].c) {
				tableIndex = i;
				break;
			}
		}
		HuffmanCode currentCode = table[tableIndex].h;
		for (int i = 0; i < currentCode.length; i++) {
			if (bitsPacked < 7) {
				out = push_bin(out, currentCode.num[i]);
				bitsPacked++;
			} else if (bitsPacked == 7) {
				out = push_bin(out, currentCode.num[i]);
				bitsPacked = 0;
				fwrite(&out, sizeof(out), 1, newFile);
				out = 0;
			}
		}
	}
	out = out << (8 - bitsPacked);
	fwrite(&out, sizeof(out), 1, newFile);
	fclose(newFile);
}

void uncompressFile(char *fileName, char *freqFileName)
{
	FILE *freqFile = fopen(freqFileName, "r");
	if (freqFile == NULL) {
		printf("Error: No se pudo abrir el archivo %s\n\n", freqFileName);
		exit(1);
	}
	int numNodos;
	Arbol *nodos = get_frequencies(freqFile, true, &numNodos);
	Arbol finalTree = Construir_Arbol(nodos, numNodos);

	Code *table = Obtener_Tabla(finalTree, numNodos);
	printTable(table, numNodos);

	FILE *compFile = fopen("codificacion.dat", "r");
	FILE *newFile = fopen("out.file", "w");
	int bitsRead = 0;
	int i;
	Arbol auxArbol = finalTree;
	uint8_t buffer;
	fread(&buffer, sizeof(buffer), 1, compFile);
	while (true) {
		if (bitsRead > 7) {
			if (fread(&buffer, sizeof(buffer), 1, compFile) != 1)
				break;
			bitsRead = 0;
		}
		int bit = get_bit(buffer, 7 - bitsRead);
		bitsRead++;
		if (bit == 0) {
			auxArbol = auxArbol->izq;
		} else {
			auxArbol = auxArbol->der;
		}
		if (Es_Hoja(auxArbol)) {
			fwrite(&auxArbol->c, sizeof(auxArbol->c), 1, newFile);
			auxArbol = finalTree;
		}
	}
	fclose(compFile);
	fclose(newFile);
}


Arbol *get_frequencies(FILE *file, bool isExplicit, int *size)
{
	Arbol *frequency = malloc(256 * sizeof(*frequency));
	if (isExplicit) {
		uint8_t buffer[60];
		int i = 0;
		while (fgets((char *)buffer, 50, file) != NULL && i < 256) {
			uint8_t c;
			int f;
			if (buffer[0] == '\'')
				sscanf((char *)buffer, "'%c'--%d", &c, &f);
			else
				sscanf((char *)buffer, "%hhd--%d", &c, &f);
			frequency[i] = Crear_Nodo(c, f);
			i++;
		}
		*size = i;
		return frequency;
	}
	for (int i = 0; i < 256; i++) {
		frequency[i] = Crear_Nodo(i, 0);
	}
	uint8_t buffer;
	while (fread(&buffer, sizeof(buffer), 1, file) == 1) {
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
	return NULL;
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