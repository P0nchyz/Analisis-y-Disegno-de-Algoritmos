#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../search.h"
#include "../BST.h"

#define THREAD_NUM 16
typedef struct {
	int *array;
	int target;
	unsigned int start;
	unsigned int end;
	int *index;
} searchInfo;

static void *t_linear_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	for (int i = search->start; i < search->end; i++) {
		if (*(search->index) != -1)
			return NULL;
		if (search->array[i] == search->target) {
			*(search->index) = i;
			break;
		}
	}
	return NULL;
}

int thread_linear_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	int *sharedIndex = malloc(sizeof(*sharedIndex));
	*sharedIndex = -1;
	searchInfo *subSearchInfo = malloc(THREAD_NUM * sizeof(*subSearchInfo));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		subSearchInfo[i].array = array;
		subSearchInfo[i].target = target;
		subSearchInfo[i].start = i * range;
		subSearchInfo[i].end = (i == THREAD_NUM - 1) ? size : (i + 1) * range;
		subSearchInfo[i].index = sharedIndex;
		pthread_create(&thread[i], NULL, t_linear_search, (void *)&subSearchInfo[i]);
	}
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], NULL);
	}
	free(thread);
	if (*sharedIndex != -1) {
		int index = *sharedIndex;
		free(sharedIndex);
		return index;
	}
	return -1;
}

static void *t_binary_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	int lower = search->start;
	int higher = search->end;
	while (higher >= lower) {
		if (*(search->index) != -1)
			return NULL;
		int middle = lower + (higher - lower) / 2;
		int middleValue = search->array[middle];
		if (middleValue == search->target) {
			*(search->index) = middle;
			return NULL;
		}
		if (search->target > middleValue)
			lower = middle + 1;
		else
			higher = middle - 1;
	}
	return NULL;
}

int thread_binary_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	int *sharedIndex = malloc(sizeof(*sharedIndex));
	*sharedIndex = -1;
	searchInfo *subSearchInfo = malloc(THREAD_NUM * sizeof(*subSearchInfo));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		subSearchInfo[i].array = array;
		subSearchInfo[i].target = target;
		subSearchInfo[i].start = i * range;
		subSearchInfo[i].end = (i == THREAD_NUM - 1) ? size : (i + 1) * range;
		subSearchInfo[i].index = sharedIndex;
		pthread_create(&thread[i], NULL, t_binary_search, (void *)&subSearchInfo[i]);
	}
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], NULL);
	}
	free(thread);
	if (*sharedIndex != -1) {
		int index = *sharedIndex;
		free(sharedIndex);
		return index;
	}
	return -1;
}

static void *t_binary_tree_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	BST searchTree = createBST();
	for (int i = search->start; i < search->end; i++)
		searchTree = insertBST(searchTree, search->array[i], i);
	int index = searchBST(searchTree, search->target);
	freeBST(searchTree);
	if (index != -1) {
		*(search->index) = index;
		return NULL;
	}
	return NULL;
}

int thread_binary_tree_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	int *sharedIndex = malloc(sizeof(*sharedIndex));
	*sharedIndex = -1;
	searchInfo *subSearchInfo = malloc(THREAD_NUM * sizeof(*subSearchInfo));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		subSearchInfo[i].array = array;
		subSearchInfo[i].target = target;
		subSearchInfo[i].start = i * range;
		subSearchInfo[i].end = (i == THREAD_NUM - 1) ? size : (i + 1) * range;
		subSearchInfo[i].index = sharedIndex;
		pthread_create(&thread[i], NULL, t_binary_tree_search, (void *)&subSearchInfo[i]);
	}
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], NULL);
	}
	free(thread);
	if (*sharedIndex != -1) {
		int index = *sharedIndex;
		free(sharedIndex);
		return index;
	}
	return -1;
}

static void *t_exponential_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	int internalSize = search->end - search->start;
	int *internalArray = &(search->array[search->start]);
	int exponentialIndex = 1;
	while ((exponentialIndex * 2) < internalSize && internalArray[exponentialIndex] < search->target)
		exponentialIndex *= 2;
	int lower = exponentialIndex / 2;
	int higher = exponentialIndex;
	while (higher >= lower) {
		if (*(search->index) != -1)
			return NULL;
		int middle = lower + (higher - lower) / 2;
		if (internalArray[middle] == search->target) {
			*(search->index) = search->start + middle;
			return NULL;
		}
		if (search->target > internalArray[middle])
			lower = middle + 1;
		else
			higher = middle - 1;
	}
	return NULL;
}

int thread_exponential_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	int *sharedIndex = malloc(sizeof(*sharedIndex));
	*sharedIndex = -1;
	searchInfo *subSearchInfo = malloc(THREAD_NUM * sizeof(*subSearchInfo));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		subSearchInfo[i].array = array;
		subSearchInfo[i].target = target;
		subSearchInfo[i].start = i * range;
		subSearchInfo[i].end = (i == THREAD_NUM - 1) ? size : (i + 1) * range;
		subSearchInfo[i].index = sharedIndex;
		pthread_create(&thread[i], NULL, t_exponential_search, (void *)&subSearchInfo[i]);
	}
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], NULL);
	}
	free(thread);
	if (*sharedIndex != -1) {
		int index = *sharedIndex;
		free(sharedIndex);
		return index;
	}
	return -1;
}

static void *t_fibonacci_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	int fib_prev2 = 0;
	int fib_prev1 = 1;
	int fib_current = fib_prev1 + fib_prev2;
	int size = search->end - search->start;


	// Encuentra el menor número de Fibonacci >= size
	while (fib_current < size) {
		fib_prev2 = fib_prev1;
		fib_prev1 = fib_current;
		fib_current = fib_prev1 + fib_prev2;
	}

	int search_start = -1;

	while (fib_current > 1) {
		if (*(search->index) != -1)
			return NULL;
		int i = (search_start + fib_prev2 < size - 1) ? (search_start + fib_prev2) : (size - 1);
		int index = search->start + i;

		if (search->array[index] < search->target) {
			fib_current = fib_prev1;
			fib_prev1 = fib_prev2;
			fib_prev2 = fib_current - fib_prev1;
			search_start = i;
		} else if (search->array[index] > search->target) {
			fib_current = fib_prev2;
			fib_prev1 = fib_prev1 - fib_prev2;
			fib_prev2 = fib_current - fib_prev1;
		} else {
			*(search->index) = index;
			return NULL;
		}
	}
	// Comparar el último elemento restante
	if (fib_prev1 && search_start + 1 < size && search->array[search->start + search_start + 1] == search->target) {
		*(search->index) = search->start + search_start + 1;
		return NULL;
	}

	return NULL;
}

int thread_fibonacci_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	int *sharedIndex = malloc(sizeof(*sharedIndex));
	*sharedIndex = -1;
	searchInfo *subSearchInfo = malloc(THREAD_NUM * sizeof(*subSearchInfo));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		subSearchInfo[i].array = array;
		subSearchInfo[i].target = target;
		subSearchInfo[i].start = i * range;
		subSearchInfo[i].end = (i == THREAD_NUM - 1) ? size : (i + 1) * range;
		subSearchInfo[i].index = sharedIndex;
		pthread_create(&thread[i], NULL, t_fibonacci_search, (void *)&subSearchInfo[i]);
	}
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], NULL);
	}
	free(thread);
	if (*sharedIndex != -1) {
		int index = *sharedIndex;
		free(sharedIndex);
		return index;
	}
	return -1;
}