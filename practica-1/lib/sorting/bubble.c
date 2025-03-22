/**
 * @file bubble.c
 * 
 * @brief Contains the implementation of the bubble sort algorithms.
 * 
 * @author Bautista Quijano Anayeli
 * @author Garcia Morian Julio Amauri
 * @author Jimenez Rodriguez Alan Gael Gael
 * @author Hernandez Zamora Valeria
 * @author Lechuga Torres Diego
 * @author Segundo Cantero Jonathan Axel
 * @author Vergara Gamboa Jose Alfonso
 * @date Oct-2024 - Mar-2025
 */

#include <stdbool.h>

void bubble_sort(int *array, unsigned int size)
{
	for (int i = 0; i < size - 1; i++) {
		// Disminuye el tamaño que debe recorrer por cada iteracion del ciclo exterior
		for (int j = 0; j < (size - 1) ; j++) {
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
	return;
}

void optimized_bubble_sort_1(int *array, unsigned int size)
{
	for (int i = 0; i < size - 1; i++) {
		// Disminuye el tamaño que debe recorrer por cada iteracion del ciclo exterior
		for (int j = 0; j < (size - 1) - i; j++) {
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
	return;
}

void optimized_bubble_sort_2(int *array, unsigned int size)
{
	bool hasChanged = true;
	for (int i = 0; i < size - 1 && hasChanged != false; i++) {
		hasChanged = false;
		// Disminuye el tamaño que debe recorrer por cada iteracion del ciclo exterior
		for (int j = 0; j < (size - 1) - i; j++) {
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				hasChanged = true;
			}
		}
	}
	return;
}