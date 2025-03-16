void bubble_sort(int *array, unsigned int size)
{
	for (int i = 0; i < size - 1; i++) {
		// Disminuye el tamaño que debe recorrer por cada iteracion del ciclo exterior
		for (int j = 0; j < (size - 1) - i; j++) {
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
	return;
}

void optimized_bubble_sort_1(int *array, unsigned int size)
{
	return;
}

void optimized_bubble_sort_2(int *array, unsigned int size)
{
	return;
}