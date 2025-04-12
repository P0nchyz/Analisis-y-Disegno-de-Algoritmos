#include <stdlib.h>

#include "BST.h"

BST createBST(void)
{
	BST retBST = NULL;
	return retBST;
}

BST insertBST(BST tree, int value, int index)
{
	if (tree == NULL) {
		struct Node *newNode = malloc(sizeof(*newNode));
		newNode->bigLeaf = NULL;
		newNode->smallLeaf = NULL;
		newNode->value = value;
		newNode->index = index;
		return newNode;
	}
	if (value > tree->value) {
		tree->bigLeaf = insertBST(tree->bigLeaf, value, index);
	} else {
		tree->smallLeaf = insertBST(tree->smallLeaf, value, index);
	}
	return tree;
}

int searchBST(BST tree, int value)
{
	if (tree == NULL)
		return -1;
	if (tree->value == value)
		return tree->index;
	if (value > tree->value)
		return searchBST(tree->bigLeaf, value);
	return searchBST(tree->smallLeaf, value);
}