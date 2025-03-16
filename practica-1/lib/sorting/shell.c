void shell_sort(int *array, unsigned int size)
{
	// Cada iteracion divide el espacio entre los elementoes en 2 hasta llegar a uno
	for (int gap = size / 2; gap > 0; gap /= 2) {
		int b = 1;
		while (b != 0) {
			b = 0;
			for (int i = gap; i < size; i++) {
				if (array[i - gap] > array[i]) {
					int temp = array[i];
					array[i] = array[i - gap];
					array[i - gap] = temp;
					b++;
				}
			}
		}
	}
	return;
}