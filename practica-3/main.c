/**
 * @file main.c
 
 * @author Bautista Quijano Anayeli
 * @author Garcia Morlan Julio Amauri
 * @author Jimenez Rodriguez Alan Gael Gael
 * @author Hernandez Zamora Valeria
 * @author Vergara Gamboa José Alfonso
 * 
 * @date Apr-2025
 * 
 * @version 0.1.0
 * 
 * Descripcion:
 * El programa implementa un algoritmo de codificación ideado por
 * David Huffman, asi como el algoritmo para descodificar.
 * 
 * Cuando se le pasa un solo argumento al programa, este tratara de
 * codificarlo, retornando dos archivos:
 * 
 * - codificacion.dat: Contiene la codificacion en forma binaria.
 * - frecuencias.txt: Contiene la tabla de frecuencia de los bytes,
 * en forma de texto claro. Los caracteres son imprimibles se mostraran
 * dentro de comillas, mientras que los no imprimibles se representaran
 * en su forma entera.
 * 
 * Cuanod se le pasan dos argumentos el programa tratara de decodificar
 * y obtener el archivo original, reconstruyendo el arbol a partir de el
 * archivo de frecuencias.
 * 
 * El programa ademas indica diferentes detalles de los archivos de entrada
 * y salida, asi como del tiempo de ejecucion de la codificacion y decodificacion
 * de archivos.
 * 
 * 
 * Compilacion:
 *     make
 * Ejecución ./huffman.out
 * 
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Libreria para la creación y manejo de arboles, codigos de huffman y
// tablas de frecuencias
#include "lib/huffman.h"
// Libreria para el manejo de bits en tipo de dato uint8_t
#include "lib/binary.h"

/**
 * @brief Obtiene la frecuencia de los caracteres en un archivo
 * 
 * Obtiene un arreglo de arboles hoja que contienen los bytes y sus 
 * respectivas frecuencias.
 * 
 * Dependiendo de la bandera isExplicit se obtendran ya sea del archivo a codificar
 * o de un archivo con las frecuencias de forma explicita.
 * 
 * @param file Archivo a codificar | Archivo de frecuencias
 * @param isExplicit ? Obtiene la frecuencia de los bytes de un archivo : Recupera la frecuencia del archivo de frecuencias
 * @param size Direccion del entero en el que guardar el numero de arboles
 * 
 * @return Arreglo de Arboles Hoja con los caracteres y su frecuenia en orden ascendiente
 */
Arbol *get_frequencies(FILE *file, bool isExplicit, int *size);

/**
 * @brief Algoritmo de Ordenamiento QuickSort
 * 
 * @param array Arreglo de Arboles que seran ordenados de acuerdo a la frecuencia
 * @param size Numero de Arboles en el arreglo
 */
void quick_sort(Arbol *array, unsigned int size);
/**
 * @brief Muestra los detalles de la compresión
 *
 * Calcula y muestra:
 * - Tamaño del archivo original (en bytes)
 * - Tamaño del archivo codificado (en bytes)
 * - Nivel de compresión (porcentaje)
 * - Total de bits codificados (sin contar la tabla de frecuencias)
 *
 * @param original Nombre del archivo original
 * @param codificado Nombre del archivo codificado
 */
 void mostrarDetalles(char *original, char *codificado) {
    FILE *orig = fopen(original, "rb");
    FILE *cod = fopen(codificado, "rb");

    if (!orig || !cod) {
        printf("Error: no se pudieron abrir los archivos para obtener detalles.\n");
        if (orig) fclose(orig);
        if (cod) fclose(cod);
        return;
    }

    fseek(orig, 0, SEEK_END);
    long tamOriginal = ftell(orig);
    fclose(orig);

    fseek(cod, 0, SEEK_END);
    long tamCodificado = ftell(cod);
    rewind(cod);

    const char *ext = strrchr(original, '.'); //Da la extensión del archivo 
    if (ext) ext++; // Saltamos el punto

    // Leer primer byte: bits válidos en el último byte
    uint8_t bitsUltimo;
    fread(&bitsUltimo, sizeof(uint8_t), 1, cod);
    long totalBits = (tamCodificado - 1) * 8 - (8 - bitsUltimo);  // -1 por el byte inicial

    fclose(cod);

    double compresion = 100.0 * (1.0 - ((double)tamCodificado / (double)tamOriginal));

    printf("\n**** Detalles de Compresion ****\n");
    printf("Archivo original: %s\n", original);
    printf("Tipo de archivo: %s\n", (ext ? ext : "Desconocido"));
    printf("Tam original     : %ld bytes\n", tamOriginal);
    printf("Tam codificado   : %ld bytes\n", tamCodificado);
    printf("Compresion alcanzada: %.2f%%\n", compresion);
    printf("Bits codificados    : %ld bits\n", totalBits);
    printf("*******************************\n");
}


/**
 * @brief Codifica el archivo utilizando el algoritmo de huffman
 * 
 * La función abre el archivo referenciado por fileName, y lo codifica
 * con el algoritmo de huffman, creando dos nuevos archivos:
 * 
 * - codificacion.dat: Codificacion en forma binaria
 * - frecuencias.txt: Lista de frecuencias de bytes
 * 
 * @param fileName Dirección del archivo a codificar
 */
void compressFile(char *fileName);

/**
 * @brief Decodifica el archivo original
 * 
 * La funcion utiliza el archivo de frecuencias para reconstruir el arbol de huffman
 * original, y lo usa para transformar la codificacion en binario en el
 * archivo original.
 * 
 * @param fileName Referencia al archivo con la codificacion en forma binaria
 * @param freqFileName Referencia al archivo con las frecuencias de bytes
 
 * @note Esta funcion crea un archivo llamado out.file
 */
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

/**
 * @brief Codifica el archivo utilizando el algoritmo de huffman
 * 
 * La función abre el archivo referenciado por fileName, y lo codifica
 * con el algoritmo de huffman, creando dos nuevos archivos:
 * 
 * - codificacion.dat: Codificacion en forma binaria
 * - frecuencias.txt: Lista de frecuencias de bytes
 * 
 * @param fileName Dirección del archivo a codificar
 */
void compressFile(char *fileName)
{
	FILE *file = fopen(fileName, "r"); //< Archivo de entrada a codificar
	if (file == NULL) {
		printf("Error: No se pudo abrir el archivo %s\n\n", fileName);
		exit(1);
	}

	int numNodos;
	Arbol *nodos = get_frequencies(file, false, &numNodos); //< Arreglo de arboles con los caracteres y su frecuencia

	FILE *freqFile = fopen("./out/frequencias.txt", "w"); //< Archivo que guardara las frecuencias en texto
	// Iteramos los nodos e imprimimos en el archvo de frecuencias la informacion contenida en estos
	for (int i = 0; i < numNodos; i++) {
		if (isprint(nodos[i]->c)) {
			// Si el caracter es imprimible lo imprimos en comillas
			fprintf(freqFile, "'%c'--%d\n", nodos[i]->c, nodos[i]->f);
		} else {
			// Si no es imprimible imprimimos su representación numerica
			fprintf(freqFile, "%d--%d\n", nodos[i]->c, nodos[i]->f);
		}
	}
	fclose(freqFile);

	Arbol finalTree = Construir_Arbol(nodos, numNodos); //< El Arbol ya formado con los bytes y sus frecuencias 

	Code *table = Obtener_Tabla(finalTree, numNodos); //< Tabla con los caracteres y sus codigos de huffman
	
	// printTable(table, numNodos); // FOR DEBUGGING

	FILE *newFile = fopen("./out/codificacion.dat", "w"); //< Archivo que contendra la codificacion binaria
	uint8_t buffer; //< Espacio para guardar un byte de memoria al leer
	// Nos aaseguramos de estar al inicio del archivo
	rewind(file);
	uint8_t out = 0; //< Espacio de un byte que guardaremos en el archivo de salida
	int bitsPacked = 0; //< Numero de bits que hemos guardado en el byte out

	fwrite(&out, sizeof(out), 1, newFile);
	// El loop correra mientras podamos leer bytes del archivo de entrada
	while (fread(&buffer, sizeof(buffer), 1, file)) { // Leemos un byte del archivo a la vez
		int tableIndex = 0; //< Posicion en la tabla en la que se encuentra el byte que leimos
		// Iteramos la tabla hasta encontrar el elemento con el caracter que leimos del archivo
		for (int i = 0; i < numNodos; i++) {
			if (buffer == table[i].c) {
				tableIndex = i;
				break;
			}
		}
		HuffmanCode currentCode = table[tableIndex].h; //< El caracter y su codigo huffman corresponiente

		// Iteramos a traves de los bits del codigo huffman que le corresponde al caracter
		for (int i = 0; i < currentCode.length; i++) {
			if (bitsPacked < 7) {
				// Si hemos guardado menos de 7 bits en el byte de salida guardamos el bit
				// correspondiente del codigo huffman
				out = push_bin(out, currentCode.num[i]);
				bitsPacked++;
			} else if (bitsPacked == 7) {
				// Si ya hemos guardado 7 bits guardamos el octavo
				// y lo escribimos en el archivo de salida
				out = push_bin(out, currentCode.num[i]);
				// Reincicamos el numero de bits guardados
				bitsPacked = 0;
				// Escribimos el byte
				fwrite(&out, sizeof(out), 1, newFile);
				// Reseteamos el byte a 0
				out = 0;
			}
		}
	}
	// Recorremos los bits del ultimo byte a escribir hasta que queden contiguos con el resto
	out = out << (8 - bitsPacked);
	fwrite(&out, sizeof(out), 1, newFile);
	rewind(newFile);
	fwrite(&bitsPacked, 1, 1, newFile);
	fclose(newFile);

	mostrarDetalles(fileName, "./out/codificacion.dat");
}

/**
 * @brief Decodifica el archivo original
 * 
 * La funcion utiliza el archivo de frecuencias para reconstruir el arbol de huffman
 * original, y lo usa para transformar la codificacion en binario en el
 * archivo original.
 * 
 * @param fileName Referencia al archivo con la codificacion en forma binaria
 * @param freqFileName Referencia al archivo con las frecuencias de bytes
 
 * @note Esta funcion crea un archivo llamado out.file
 */
void uncompressFile(char *fileName, char *freqFileName)
{
	FILE *freqFile = fopen(freqFileName, "r"); //< Archivo de texto con las frecuencias de los bytes del archivo original
	if (freqFile == NULL) {
		printf("Error: No se pudo abrir el archivo %s\n\n", freqFileName);
		exit(1);
	}
	int numNodos;
	Arbol *nodos = get_frequencies(freqFile, true, &numNodos); //< Arreglo de arboles con los bytes y sus frecuencias

	Arbol finalTree = Construir_Arbol(nodos, numNodos); //< El arbol ya formado con los bytes y sus frecuencias

	// Code *table = Obtener_Tabla(finalTree, numNodos); //< Tabla con los caracteres y sus codigos huffman

	// printTable(table, numNodos); // FOR DEBUGGING

	FILE *compFile = fopen("./out/codificacion.dat", "r"); //< Archivo con la codificacion en binario
	FILE *newFile = fopen("./out/out.file", "w"); //< Archivo de salida con los datos del archivo original
	int bitsRead = 0; //< Numero de bits que se han leido de un byte
	Arbol auxArbol = finalTree; //< Arbol auxilar con la posicion a la que hemos traversado
	uint8_t buffer; //< Espacio para guardar un byte de memoria al leer
	
	uint8_t lastBits;
	fread(&lastBits, sizeof(lastBits), 1, compFile);
	// Leemos el primer byte del archivo
	fread(&buffer, sizeof(buffer), 1, compFile);
	// Loop infinito con condiciones de salida internas
	int reachedEOF = 1;
	while (true) { 
		if (bitsRead > 7) {
			if (reachedEOF != 1)
				break;
			// Si ya leimos los 8 bits del buffer leemos otro
			fread(&buffer, sizeof(buffer), 1, compFile);
			uint8_t nextBuff;
			reachedEOF = fread(&nextBuff, sizeof(nextBuff), 1, compFile);
			fseek(compFile, -1, SEEK_CUR);
			if (reachedEOF != 1) {
				buffer = buffer >> (8 - lastBits);
				bitsRead = 8 - lastBits;
			} else
				bitsRead = 0;
		}
		int bit = get_bit(buffer, 7 - bitsRead); //< Leemos bit por bit
		bitsRead++;
		if (bit == 0) {
			// Si el bit es 0 recorremos el arbol a la izquierda
			auxArbol = auxArbol->izq;
		} else {
			// Si el bit es 1 recorremos el arbol a la derecha
			auxArbol = auxArbol->der;
		}
		// Si el arbol es una hoja escribimos el caracter que contiene
		if (Es_Hoja(auxArbol)) {
			fwrite(&auxArbol->c, sizeof(auxArbol->c), 1, newFile);
			// Reiniciamos nuestro arbol auxiliar al arbol original
			auxArbol = finalTree;
		}
	}
	fclose(compFile);
	fclose(newFile);
}


/**
 * @brief Obtiene la frecuencia de los caracteres en un archivo
 * 
 * Obtiene un arreglo de arboles hoja que contienen los bytes y sus 
 * respectivas frecuencias.
 * 
 * Dependiendo de la bandera isExplicit se obtendran ya sea del archivo a codificar
 * o de un archivo con las frecuencias de forma explicita.
 * 
 * @param file Archivo a codificar | Archivo de frecuencias
 * @param isExplicit ? Obtiene la frecuencia de los bytes de un archivo : Recupera la frecuencia del archivo de frecuencias
 * @param size Direccion del entero en el que guardar el numero de arboles
 * 
 * @return Arreglo de Arboles Hoja con los caracteres y su frecuenia en orden ascendiente
 */
Arbol *get_frequencies(FILE *file, bool isExplicit, int *size)
{
	// Alojamos memoria para los 256 posibles arboles para cada byte y su frecuencia
	Arbol *frequency = malloc(256 * sizeof(*frequency));
	// Si ya tenemos las frecuencias de forma explicita en un archivo, las recuperamos
	if (isExplicit) {
		uint8_t buffer[60]; //< Buffer de bytes para leer del archivo
		int i = 0; //< Iterador con la posicion de nodo en la que nos encontramos
		// Leemos una linea del archivo de a lo mucho 49 caracteres
		while (fgets((char *)buffer, 50, file) != NULL && i < 256) {
			uint8_t c; //< Caracter al que corresponde la frecuencia
			int f; //<  Frecuencia
			if (buffer[0] == '\'') // Si el primer caracter de la linea es una comilla
				sscanf((char *)buffer, "'%c'--%d", &c, &f); // Tratamos el primer argumento como un caracter
			else // Si no
				sscanf((char *)buffer, "%hhd--%d", &c, &f); // Tratamos el primer argumento como un entero de 8 bits
			// Creamos un nodo con el caracter y la frecuencia y lo guardamos en el arreglo
			frequency[i] = Crear_Nodo(c, f);
			i++;
		}
		// Guardamos en la posicion de memoria size el tamaño del arreglo
		*size = i;
		// Retornamos un apuntador a el arreglo de arboles
		return frequency;
	}

	// Si no tenemos las frecuencias de manera explicita la obtenemos contando las veces
	// que aparecen los bytes dentro del archivo

	// Inicializamos todos los nodos posibles con el caracter correspondiente y frecuencia de 0
	for (int i = 0; i < 256; i++) {
		frequency[i] = Crear_Nodo(i, 0);
	}
	uint8_t buffer; //< Espacio de un byte para guarda lo que leemos del archivo
	// Ciclo que correra mientras podamos leer un byte del archivo
	while (fread(&buffer, sizeof(buffer), 1, file) == 1) {
		// Aumentamos la frecuencia del nodo que representa el byte que acabamos de leer
		frequency[buffer]->f++;
	}
	// Ordenamos los nodos de manera ascendiente
	quick_sort(frequency, 256);
	int nonZeroItems = 256; //< Contador con cuantos bytes aparecen al menos una vez
	for (int i = 0; i < 256; i++) {
		// Si la frecuencia es 0 no aparece en el archivo
		if (frequency[i]->f == 0) {
			// Reducimos el numero de elementos que aparecen al menos una vez
			nonZeroItems--;
			// Liberamos la memoria del nodo
			free(frequency[i]);
			frequency[i] = NULL;
			continue;
		}
		// Guradamos en la posicion de memoria size el tamaño del arreglo
		*size = nonZeroItems;
		// Regresamos un apuntador al primer Arbol con un caracter que aparece al menos una vez
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
