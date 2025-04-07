#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../search.h"

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
	if (sharedIndex != -1) {
		int index = *sharedIndex;
		free(sharedIndex);
		return index;
	}
	return -1;
}

static void *t_binary_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	int *array = search->array;
	unsigned int start = search->start;
	unsigned int end = search->end;
	
}

int thread_binary_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		searchInfo currentSubArray = {.array = array, .target = target, .start = i * range, .end = (i + 1) * range - 1};
		pthread_create(&thread[i], NULL, t_binary_search, (void *)&currentSubArray);
	}
	int **indexArray = malloc(THREAD_NUM * sizeof(*indexArray));
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], (void *)&indexArray[i]);
	}
	free(thread);
	for (int i = 0; i < THREAD_NUM; i++) {
		if (*indexArray[i] != -1) {
			free(indexArray);
			return *indexArray[i];
		}
	}
	return -1;
}

static void *t_binary_tree_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	int *array = search->array;
	unsigned int start = search->start;
	unsigned int end = search->end;
	
}

int thread_binary_tree_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		searchInfo currentSubArray = {.array = array, .target = target, .start = i * range, .end = (i + 1) * range - 1};
		pthread_create(&thread[i], NULL, t_binary_tree_search, (void *)&currentSubArray);
	}
	int **indexArray = malloc(THREAD_NUM * sizeof(*indexArray));
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], (void *)&indexArray[i]);
	}
	free(thread);
	for (int i = 0; i < THREAD_NUM; i++) {
		if (*indexArray[i] != -1) {
			free(indexArray);
			return *indexArray[i];
		}
	}
	return -1;
}

static void *t_exponential_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	int *array = search->array;
	unsigned int start = search->start;
	unsigned int end = search->end;
	
}

int thread_exponential_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		searchInfo currentSubArray = {.array = array, .target = target, .start = i * range, .end = (i + 1) * range - 1};
		pthread_create(&thread[i], NULL, t_exponential_search, (void *)&currentSubArray);
	}
	int **indexArray = malloc(THREAD_NUM * sizeof(*indexArray));
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], (void *)&indexArray[i]);
	}
	free(thread);
	for (int i = 0; i < THREAD_NUM; i++) {
		if (*indexArray[i] != -1) {
			free(indexArray);
			return *indexArray[i];
		}
	}
	return -1;
}

static void *t_fibonacci_search(void *arg)
{
	searchInfo *search = (searchInfo *)arg;
	int *array = search->array;
	unsigned int start = search->start;
	unsigned int end = search->end;
	
}

int thread_fibonacci_search(int *array, unsigned int size, int target)
{
	pthread_t *thread= malloc(THREAD_NUM * sizeof(*thread));
	for (int i = 0; i < THREAD_NUM; i++) {
		int range = size / THREAD_NUM;
		searchInfo currentSubArray = {.array = array, .target = target, .start = i * range, .end = (i + 1) * range - 1};
		pthread_create(&thread[i], NULL, t_fibonacci_search, (void *)&currentSubArray);
	}
	int **indexArray = malloc(THREAD_NUM * sizeof(*indexArray));
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thread[i], (void *)&indexArray[i]);
	}
	free(thread);
	for (int i = 0; i < THREAD_NUM; i++) {
		if (*indexArray[i] != -1) {
			free(indexArray);
			return *indexArray[i];
		}
	}
	return -1;
}