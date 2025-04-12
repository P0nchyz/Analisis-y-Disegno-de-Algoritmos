#ifndef BST_H
#define BST_H

struct Node {
	int value;
	int index;
	struct Node *smallLeaf;
	struct Node *bigLeaf;
};

typedef struct Node *BST;

BST createBST(void);

BST insertBST(BST tree, int value, int index);

int searchBST(BST tree, int value);

void freeBST(BST tree);

#endif
