#include <stdlib.h>

void merge(int *leftArray, int sizeLeftArray, int *rightArray, int sizeRightArray, int *array, int size);

void merge_sort(int *array, unsigned int size)
{
	if (size <= 1)
		return;

	int middle = size / 2;
	// leftArray es una referencia al primer elemento del array
	int *leftArray = array;
	int sizeLeftArray = middle;
	// rightArray es una referencia al elemento a la mitad del array
	int *rightArray = array + middle;
	int sizeRightArray = size - middle;

	merge_sort(leftArray, sizeLeftArray);
	merge_sort(rightArray, sizeRightArray);

	merge(leftArray, sizeLeftArray, rightArray, sizeRightArray, array, size);

	return;
}

void merge(int *leftArray, int sizeLeftArray, int *rightArray, int sizeRightArray, int *array, int size)
{
	int leftIndex = 0;
	int rightIndex = 0;
	int *tempArray = malloc(size * sizeof(*tempArray));
	// Recorrer todos los espacios del arreglo principal
	for (int i = 0; i < size; i++) {
		if (leftIndex < sizeLeftArray && rightIndex < sizeRightArray) {
			if (leftArray[leftIndex] > rightArray[rightIndex]) {
				tempArray[i] = rightArray[rightIndex];
				rightIndex++;
			} else {
				tempArray[i] = leftArray[leftIndex];
				leftIndex++;
			}
		} else if (leftIndex < sizeLeftArray) {
			tempArray[i] = leftArray[leftIndex];
			leftIndex++;
		} else {
			tempArray[i] = rightArray[rightIndex];
			rightIndex++;
		}
	}
	for (int i = 0; i < size; i++) {
		array[i] = tempArray[i];
	}
	free(tempArray);
}