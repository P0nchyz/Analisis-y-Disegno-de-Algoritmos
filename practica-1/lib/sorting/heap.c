/* 
 * @author Bautista Quijano Anayeli
 * @author Garcia Morian Julio Amauri
 * @author Jimenez Rodriguez Alan Gael Gael
 * @author Hernandez Zamora Valeria
 * @author Lechuga Torres Diego
 * @author Segundo Cantero Jonathan Axel
 * @author Vergara Gamboa Jose Alfonso
 Descripcion: Ordena un arreglo de manera ascendente 
*/

void heapify(int *array, unsigned int size, int index);

void heap_sort(int *array, unsigned int size)
{
	/*
	El for comienza desde el ultimo nodo que no sea considerado una hoja.
	Heapify:Garantiza que el elemento mas grande del array quede en la raiz.
 	*/
	for (int i = (size / 2) - 1; i >= 0; i--)
		heapify(array, size, i);
	/*
 	Comienza el ordenamiento intercambiando el elemento mas grande del array con el ultimo elemento de este 

  	heapify reduce el tamanio del heap en 1 ignorando el elemento que ya se ha ordenado 
 	*/
	for (int i = size - 1; i > 0; i--) {
		int temp = array[0];
		array[0] = array[i];
		array[i] = temp;

		heapify(array, i, 0);
	}
	return;
}
/*

*/
void heapify(int *array, unsigned int size, int index)
{
	//Incializa el ms grande como el nodo actual
	int largest = index;
	//Indice del lado izqu
	int left = 2 * index + 1;
	//Indice del lado der
	int right = 2 * index + 2;

	/*
 	Comparacion de los ambos lados (Derecho e izquierdo)
  	ara encontrar el nodo mas grande, dependiendo de donde se encuentre el nodo mas 
   	grande se actualizara el index y lo hara el nodo mas grade 
 	*/
	if (left < size && array[left] > array[largest])
		largest = left;
	if (right < size && array[right] > array[largest])
		largest = right;

	/*
 	Intercambia el index del nodo mayor en caso de ser necesario y continua de manera 
  	recursiva todo el proceso 
 	*/
	if (largest != index) {
		int temp = array[index];
		array[index] = array[largest];
		array[largest] = temp;

		heapify(array, size, largest);
	}

}
