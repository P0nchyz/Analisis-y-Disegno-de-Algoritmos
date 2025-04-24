#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.c"

typedef struct{
	unsigned char c;
	int f;
} Pair;

Pair *get_frequencies(FILE *file);
void quick_sort(Pair *array, unsigned int size);



int main(int argc, char *argv[])
{
	char file_name[100];
	strcpy(file_name, argv[1]);
	FILE *file = fopen(file_name, "r");
	if(file == NULL) {
		printf("Error: No se pudo abrir el archivo\n\n");
		exit (1);
	}

	Pair *frequency = get_frequencies(file);

	quick_sort(frequency, 256);
	for(int i=0; i<256; i++){
		printf("%d - %d\n", frequency[i].c, frequency[i].f);
	}

	int num_unique = 0;
	for (int i = 0; i < 256; i++) {
		if (frequency[i].f != 0) {
			num_unique = 256 - i;
			break;
		}
	}
	printf("\n\n%d\n\n", num_unique);

	Arbol *nodos = malloc(num_unique * sizeof(*nodos));
	for (int i = 0; i < num_unique; i++) {
		int index = 256 - num_unique + i;
		nodos[i] = Crear_Nodo(frequency[index].c, frequency[index].f);
	}

	for (int i = 0; i < num_unique; i++) {
		printf("**** %d - %d\n", nodos[i]->caracter, nodos[i]->frecuencia);
	}

	fclose(file);

}


Pair *get_frequencies(FILE *file)
{
	Pair *frequency = malloc(256 * sizeof(*frequency));

	for (int i = 0; i < 256; i++) {
		frequency[i].c = i;
		frequency[i].f = 0;
	}

	fseek(file, 0, SEEK_END); //Nos posicionamos al final del archivo
	unsigned long file_size = ftell(file); //Nos dice la posicion 
	rewind(file); //Nos manda al principio del archivo
	
	for (int i = 0; i < file_size; i++) {
		unsigned char buffer;
		fread(&buffer, sizeof(char), 1, file); //Lee un caracter
		frequency[buffer].f++;
	}

	return frequency;
}

int findPivot(Pair *array, int size)
{
	// Selecciona el ultimo elemento como pivote
	int pivot = array[size - 1].f;
	// Indice comienza fuera del arreglo
	int i = -1;
	// Recorre todos los elementos del arreglo menos el ultimo (pivote)
	for (int j = 0; j < size - 1; j++) {
		// Si el elemento en el indice j es menor que el pivote se intercambia con el elemento en i
		// el elemento en i corresponde al elemento mas pequeño
		if (array[j].f < pivot) {
			i++;
			Pair temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	// Se incrementa i para obtener la posicion del pivote y se intercambia a su posicion final
	i++;
	Pair temp = array[i];
	array[i] = array[size - 1];
	array[size - 1] = temp;
	return i;
}

void quick_sort(Pair *array, unsigned int size)
{
	if (size <= 1)
		return;
	
	int pivot = findPivot(array, size);
	// leftArray es una referencia al principio del array
	Pair *leftArray = array;
	// poniendo el tamaño como el valor de pivot nos aseguramos que el array acabe uno antes del pivote
	unsigned int leftSize = pivot;
	quick_sort(leftArray, leftSize);
	// rightArray es una referencia a el elemento despues del pivote
	Pair *rightArray = array + pivot + 1;
	unsigned int rightSize = size - (leftSize + 1);
	quick_sort(rightArray, rightSize);

	return;
}
