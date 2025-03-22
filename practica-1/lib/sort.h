/**
 * @file sort.h
 * @brief Header for Different Sorting Functions.
 * @author José Vergara
 */

/**
 * @brief Bubble Sort Algorithm.
 * 
 * Compares two elements and moves the bigger one to the right
 * 
 * O(n^2)
 * 
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void bubble_sort(int *array, unsigned int size);

/**
 * @brief Bubble Sort Algorithm.
 * 
 * Compares two elements and moves the bigger one to the right
 * 
 * Optimization: Makes the inside loop check fewer items as the right
 * side gets sorted.
 * 
 * O(n^2)
 * 
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void optimized_bubble_sort_1(int *array, unsigned int size);

/**
 * @brief Bubble Sort Algorithm.
 * 
 * Compares two elements and moves the bigger one to the right
 * 
 * Optimization: Includes optimization from @ref optimized_bubble_sort_1
 * and has a boolean flag for checking if the array is sorted in the inside
 * loop, preventing the possible additional iterations if the array was already sorted.
 * 
 * O(n^2)
 * 
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void optimized_bubble_sort_2(int *array, unsigned int size);

/**
 * @brief Insertion Sort Algorithm.
 * 
 * Selects an element in the array and compares it to all the
 * elements already sorted, until it finds a smaller one.
 * 
 * O(n^2)
 * 
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void insertion_sort(int *array, unsigned int size);

/**
 * @brief Selection Sort Algorithm.
 * 
 * Finds the smallest element in the array and swaps it with the
 * first one, then finds the next smallest and swaps it with the
 * second, and so on.
 * 
 * O(n^2)
 * 
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void selection_sort(int *array, unsigned int size);

/**
 * @brief Shell Sort Algorithm.
 * 
 * It's a generalization of the @ref selection_sort algorithm.
 * Compares the elements across a gap which partially sorts the array while
 * moving the extreme items further to the sides. The gap reduces across each
 * iteration, until it performs what is essentially a selection sort when the gap
 * is one element apart.
 * 
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void shell_sort(int *array, unsigned int size);

void tree_sort(int *array, unsigned int size);

/**
 * @brief Merge Sort Algorithm.
 * 
 * Recursive sorting algorithm that divides an array in two
 * until getting a single element array and then merges them.
 * 
 * O(n log n)
 *
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void merge_sort(int *array, unsigned int size);

/**
 * @brief Quick Sort Algorithm.
 * 
 * Recursive sorting algorithm.
 * 
 * Using a pivot value divides the array in two sections, one with numbers smaller
 * than the pivot value and one with numbers bigger than the pivot
 * without including the pivot, and passes both array sections to another
 * quick_sort instance.
 * 
 * O(n log n) on average
 *
 * @param array Pointer to integers to be sorted
 * @param size Number of elements in the array
 */
void quick_sort(int *array, unsigned int size);

void heap_sort(int *array, unsigned int size);