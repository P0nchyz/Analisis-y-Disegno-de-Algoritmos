#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.c"


struct Par{
	unsigned char caracter;
	int frecuencia;
};

int *obtener_frecuencias(FILE *file);
void quick_sort(struct Par *array, unsigned int size);
int findPivot(struct Par *array, int size);



int main(int argc, char *argv[])
{
	//Contamos frecuencias************

	char file_name[100];
	strcpy(file_name, argv[1]);
	FILE *file = fopen(file_name, "r");
	
	if(file==NULL)
	{
		printf("Error: No se pudo abrir el archivo\n\n");

		exit (1);
	}

	int *frecuencia = obtener_frecuencias(file);

	struct Par charfreq [256];
	for(int i= 0; i<256; i++){
		charfreq[i].caracter = i;
		charfreq[i].frecuencia = frecuencia[i];
	}


	free(frecuencia);

	quick_sort(charfreq, 256);
	for(int i=0; i<256; i++){
		printf("%d - %d\n",charfreq[i].caracter,charfreq[i].frecuencia);
	}
	int num_unique = 0;
	for (int i = 0; i < 256; i++) {
		if (charfreq[i].frecuencia != 0) {
			num_unique = 256 - i;
			break;
		}
	}
	printf("\n\n%d\n\n", num_unique);

	Arbol *nodos = malloc(num_unique * sizeof(Arbol));
	for (int i = 0; i < num_unique; i++) {
		int index = 256 - num_unique + i;
		nodos[i] = Crear_Nodo(charfreq[index].caracter, charfreq[index].frecuencia);
	}

	for (int i = 0; i < num_unique; i++) {
		printf("**** %d - %d\n", nodos[i]->caracter, nodos[i]->frecuencia);
	}

	fclose(file);

}


int *obtener_frecuencias(FILE *file)
{
	int *frecuencia = malloc(256*sizeof (int));

	for(int i=0; i<256; i++)
	{
		frecuencia[i] = 0;
	}

	fseek(file, 0, SEEK_END); //Nos posicionamos al final del archivo
	unsigned long file_size = ftell(file); //Nos dice la posicion 
	rewind(file); //Nos manda al principio del archivo
	
	for(int i=0; i<file_size; i++)
	{
		unsigned char buffer;
		fread(&buffer, sizeof(char), 1, file); //Lee un caracter
		frecuencia[buffer]++;
	}

	return frecuencia;
}


void quick_sort(struct Par *array, unsigned int size)
{
	if (size <= 1)
		return;
	
	int pivot = findPivot(array, size);
	// leftArray es una referencia al principio del array
	struct Par *leftArray = array;
	// poniendo el tamaño como el valor de pivot nos aseguramos que el array acabe uno antes del pivote
	int leftSize = pivot;
	quick_sort(leftArray, leftSize);
	// rightArray es una referencia a el elemento despues del pivote
	struct Par *rightArray = array + pivot + 1;
	int rightSize = size - (leftSize + 1);
	quick_sort(rightArray, rightSize);

	return;
}

int findPivot(struct Par *array, int size)
{
	// Selecciona el ultimo elemento como pivote
	int pivot = array[size - 1].frecuencia;
	// Indice comienza fuera del arreglo
	int i = -1;
	// Recorre todos los elementos del arreglo menos el ultimo (pivote)
	for (int j = 0; j < size - 1; j++) {
		// Si el elemento en el indice j es menor que el pivote se intercambia con el elemento en i
		// el elemento en i corresponde al elemento mas pequeño
		if (array[j].frecuencia < pivot) {
			i++;
			struct Par temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	// Se incrementa i para obtener la posicion del pivote y se intercambia a su posicion final
	i++;
	struct Par temp = array[i];
	array[i] = array[size - 1];
	array[size - 1] = temp;
	return i;
}