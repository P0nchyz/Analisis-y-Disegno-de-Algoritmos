#include "../BST.h"

void tree_sort(int *array, unsigned int size)
{
	BST myBST = createBST();
	for (int i = 0; i < size; i++) {
		myBST = insertBST(myBST, array[i]);
	}
	int index = 0;
	saveInOrderTraversalBST(myBST, array, &index);
	return;
}