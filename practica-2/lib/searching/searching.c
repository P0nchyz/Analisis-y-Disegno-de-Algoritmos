#include "../search.h"
#include "../BST.h"

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
		
		if (target > array[middle])
			lower = middle + 1;
		else
			higher = middle - 1;
	}
	return -1;
}

int binary_tree_search(int *array, unsigned int size, int target)
{
	BST searchTree = createBST();
	for (int i = 0; i < size; i++)
		searchTree = insertBST(searchTree, array[i], i);
	return searchBST(searchTree, target);

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
		if (target > array[middle])
			lower = middle + 1;
		else
			higher = middle - 1;
	}
	return -1;
}

int fibonacci_search(int *array, unsigned int size, int target)
{
	int fib_prev2 = 0;                      // (m-2)º número de Fibonacci
	int fib_prev1 = 1;                      // (m-1)º número de Fibonacci
	int fib_current = fib_prev1 + fib_prev2; // m-ésimo número de Fibonacci

	// Encuentra el menor número de Fibonacci >= size
	while (fib_current < size) {
		fib_prev2 = fib_prev1;
		fib_prev1 = fib_current;
		fib_current = fib_prev1 + fib_prev2;
	}

	int search_start = -1;

	while (fib_current > 1) {
		int i = (search_start + fib_prev2 < size - 1) ? (search_start + fib_prev2) : (size - 1);

		if (array[i] < target) {
			fib_current = fib_prev1;
			fib_prev1 = fib_prev2;
			fib_prev2 = fib_current - fib_prev1;
			search_start = i;
		} else if (array[i] > target) {
			fib_current = fib_prev2;
			fib_prev1 = fib_prev1 - fib_prev2;
			fib_prev2 = fib_current - fib_prev1;
		} else {
			return i;
		}
	}

	// Comparar el último elemento restante
	if (fib_prev1 && search_start + 1 < size && array[search_start + 1] == target)
		return search_start + 1;

	return -1;
}
