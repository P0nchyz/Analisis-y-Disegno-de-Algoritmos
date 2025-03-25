#include <stdlib.h>

#include "BST.h"

BST createBST(void)
{
	BST retBST = NULL;
	return retBST;
}

BST insertBST(BST tree, int value)
{
	if (tree == NULL) {
		struct Node *newNode = malloc(sizeof(*newNode));
		newNode->bigLeaf = NULL;
		newNode->smallLeaf = NULL;
		newNode->value = value;
		return newNode;
	}
	if (value > tree->value) {
		tree->bigLeaf = insertBST(tree->bigLeaf, value);
	} else {
		tree->smallLeaf = insertBST(tree->smallLeaf, value);
	}
	return tree;
}

void saveInOrderTraversalBST(BST tree, int* array, int *index)
{
	if (tree != NULL) {
		saveInOrderTraversalBST(tree->smallLeaf, array, index);
		array[(*index)] = tree->value;
		(*index)++;
		saveInOrderTraversalBST(tree->bigLeaf, array, index);
	}
}