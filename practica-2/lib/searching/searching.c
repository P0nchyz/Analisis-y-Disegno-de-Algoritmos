#include "../search.h"

int linear_search(int *array, unsigned int size, int target)
{
	for (int i = 0; i < size; i++)
		if (array[i] == target)
			return i;
	return -1;
	
}

int binary_search(int *array, unsigned int size, int target)
{
	int lower = 0;
	int higher = size - 1;
	while (higher >= lower) {
		int middle = lower + (higher - lower) / 2;
		if (array[middle] == target)
			return middle;
		
		if (array[middle] > target)
			lower = middle + 1;
		else
			higher = middle - 1;
	}
	return -1;
}

int binary_tree_search(int *array, unsigned int size, int target)
{
}

int exponential_search(int *array, unsigned int size, int target)
{
	int exponentialIndex = 1;
	while ((exponentialIndex * 2) < size && array[exponentialIndex] < target)
		exponentialIndex *= 2;
	int lower = exponentialIndex / 2;
	int higher = exponentialIndex;
	while (higher >= lower) {
		int middle = lower + (higher - lower) / 2;
		if (array[middle] == target)
			return middle;
		if (array[middle] > target)
			lower = middle + 1;
		else
			higher = middle - 1;
	}
	return -1;
}

int fibonacci_search(int *array, unsigned int size, int target)
{

}