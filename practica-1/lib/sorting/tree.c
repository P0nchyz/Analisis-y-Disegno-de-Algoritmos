#include "../BST.h"
/*
* @author Bautista Quijano Anayeli
 * @author Garcia Morian Julio Amauri
 * @author Jimenez Rodriguez Alan Gael Gael
 * @author Hernandez Zamora Valeria
 * @author Lechuga Torres Diego
 * @author Segundo Cantero Jonathan Axel
 * @author Vergara Gamboa Jose Alfonso
 * Descripcion>
   Ordenamiento por tree sort usando arboles binarios de busqueda 
*/
void tree_sort(int *array, unsigned int size)
{
	/*
 	Inicializa un arbol binario de busqueda 
  	Despues inserta cda elementoen un array del BST
 	*/
	BST myBST = createBST();
	for (int i = 0; i < size; i++) {
		myBST = insertBST(myBST, array[i]);
	}
	/*
 	Realiza el recorrido de manera in/order (izquierda - Raiz - derecha) Y guarda los valores en 
  	el arreglo origial, produciendo los eementos en orden ascendente 
  	*/
	int index = 0;
	saveInOrderTraversalBST(myBST, array, &index);
	return;
}
