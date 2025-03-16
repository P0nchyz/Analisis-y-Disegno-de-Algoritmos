void selection_sort(int *array, unsigned int size)
{
	// Recorre todos los elementos del arreglo menos el ultimo
	for (int i = 0; i < size - 1; i++) {
		// Guarda el index del elemento mas pequeño encontrado
		int smallestIndex = i;
		// Recorre desde el elemento mas pequeño encontrado hacia adelante
		for (int j = smallestIndex + 1; j < size; j++) {
			// Si encuentra un elemento mas pequeño guarda su index
			if (array[j] < array[smallestIndex])
				smallestIndex = j;
		}
		int temp = array[smallestIndex];
		array[smallestIndex] = array[i];
		array[i] = temp;
	}
	return;
}