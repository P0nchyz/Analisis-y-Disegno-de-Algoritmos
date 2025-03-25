void heapify(int *array, unsigned int size, int index);

void heap_sort(int *array, unsigned int size)
{
	for (int i = (size / 2) - 1; i >= 0; i--)
		heapify(array, size, i);

	for (int i = size - 1; i > 0; i--) {
		int temp = array[0];
		array[0] = array[i];
		array[i] = temp;

		heapify(array, i, 0);
	}
	return;
}

void heapify(int *array, unsigned int size, int index)
{
	int largest = index;

	int left = 2 * index + 1;

	int right = 2 * index + 2;

	if (left < size && array[left] > array[largest])
		largest = left;
	if (right < size && array[right] > array[largest])
		largest = right;

	if (largest != index) {
		int temp = array[index];
		array[index] = array[largest];
		array[largest] = temp;

		heapify(array, size, largest);
	}

}