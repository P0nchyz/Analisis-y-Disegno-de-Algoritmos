#ifndef SEARCH_H
#define SEARCH_H

int linear_search(int *array, unsigned int size, int target);

int binary_search(int *array, unsigned int size, int target);

int binary_tree_search(int *array, unsigned int size, int target);

int exponential_search(int *array, unsigned int size, int target);

int fibonacci_search(int *array, unsigned int size, int target);

int thread_linear_search(int *array, unsigned int size, int target);

int thread_binary_search(int *array, unsigned int size, int target);

int thread_binary_tree_search(int *array, unsigned int size, int target);

int thread_exponential_search(int *array, unsigned int size, int target);

int thread_fibonacci_search(int *array, unsigned int size, int target);

#endif