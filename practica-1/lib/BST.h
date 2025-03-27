#ifndef BST_H
#define BST_H

struct Node {
	int value;
	struct Node *smallLeaf;
	struct Node *bigLeaf;
};

typedef struct Node *BST;

BST createBST(void);

BST insertBST(BST tree, int value);

void saveInOrderTraversalBST(BST tree, int* array, int *index);

#endif