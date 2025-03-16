void insertion_sort(int *array, unsigned int size)
{
	for (int i = 0; i < size; i++) {
		int j = i;
		int temp = array[i];
		for (; (j > 0) && (temp < array[j - 1]); j--) {
			array[j] = array[j - 1];
		}
		array[j] = temp;
	}
	return;
}