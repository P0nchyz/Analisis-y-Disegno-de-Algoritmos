#include <stdlib.h>
#include "../sort.h"

/**
 * @brief Merge two different arrays.
 * 
 * The input arrays are asumed to be both sorted and occupy
 * a contiguous region in memory (will not return a pointer
 * to merged arrays)
 * 
 * This function can only be called from withing this file
 * (Al chile lei por ahi sobre la keyword static y la queria usar
 * deal with it)
 * 
 * O(n)
 * 
 * @param leftArray Pointer to left side of the array
 * @param sizeLeftArray Number of elements in the left array
 * @param rightArray Pointer to right side of the array
 * @param sizeRightArray Number of elements in the right array
 * @param array Pointer to the whole array (Should be the same as leftArray, prolly bad design)
 * @param size Size of the whole array (sizeLeftArray + sizeRightArray)
 */
static void merge(int *leftArray, int sizeLeftArray, int *rightArray, int sizeRightArray, int *array, int size);

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