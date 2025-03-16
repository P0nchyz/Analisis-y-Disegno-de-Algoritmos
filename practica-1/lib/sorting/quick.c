int findPivot(int *array, int size);

void quick_sort(int *array, unsigned int size)
{
	if (size <= 1)
		return;
	
	int pivot = findPivot(array, size);
	// leftArray es una referencia al principio del array
	int *leftArray = array;
	// poniendo el tamaño como el valor de pivot nos aseguramos que el array acabe uno antes del pivote
	int leftSize = pivot;
	quick_sort(leftArray, leftSize);
	// rightArray es una referencia a el elemento despues del pivote
	int *rightArray = array + pivot + 1;
	int rightSize = size - (leftSize + 1);
	quick_sort(rightArray, rightSize);

	return;
}

int findPivot(int *array, int size)
{
	// Selecciona el ultimo elemento como pivote
	int pivot = array[size - 1];
	// Indice comienza fuera del arreglo
	int i = -1;
	// Recorre todos los elementos del arreglo menos el ultimo (pivote)
	for (int j = 0; j < size - 1; j++) {
		// Si el elemento en el indice j es menor que el pivote se intercambia con el elemento en i
		// el elemento en i corresponde al elemento mas pequeño
		if (array[j] < pivot) {
			i++;
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	// Se incrementa i para obtener la posicion del pivote y se intercambia a su posicion final
	i++;
	int temp = array[i];
	array[i] = array[size - 1];
	array[size - 1] = temp;
	return i;
}
