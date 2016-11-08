#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct RBTree {
	int key;
	int val;
	struct RBTree *right;
	struct RBTree *left;
	int n;
	int color;
};

int isRed(struct RBTree *x) {
	if (!x)
		return 0;
	return (x->color == RED);
}

struct RBTree *rotateLeft(struct RBTree *h) {
	if (!h)
		return NULL;
	struct RBTree *x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

struct RBTree *rotateRight(struct RBTree *h) {
	if (!h)
		return NULL;
	struct RBTree *x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

void flipColors(struct RBTree *h) {
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
}

struct RBTree *insert(struct RBTree *h, int key, int val) {
	if (!h) {
		h = (struct RBTree *)malloc(sizeof(struct RBTree));
		if (!h)
			return NULL;
		h->right = h->left = NULL;
		h->key = key;
		h->val = val;
		h->color = RED;
		return h;
	} else {
		int cmp = key - h->key;
		if (cmp == 0)
			h->val = val;
		else if (cmp < 0)
			h->left = insert(h->left, key , val);
		else if (cmp > 0)
			h->right = insert(h->right, key, val);

		if (isRed(h->right) && !isRed(h->left))
			h = rotateLeft(h);
		if (isRed(h->left) && isRed(h->left->left))
			h = rotateRight(h);
		if (isRed(h->right) && isRed(h->left))
			flipColors(h);
		return h;
	}
}

struct RBTree* put(int a[], int len) {
	int i;
	struct RBTree *root = NULL;
	for (i = 0; i < len; i++) {
		root = insert(root, a[i], a[i]);
		root->color = BLACK;
		//printf("%d %d\n", root->key, root->color);
	}
	return root;
}

void preOrderTraverse(struct RBTree *root) {
	if (root) {
		printf("%d %d\n", root->key, root->color);
		preOrderTraverse(root->left);
		preOrderTraverse(root->right);
	}
}

int main() {
	int i;
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};

	struct RBTree *root = NULL;

	root = put(a, 10);

	preOrderTraverse(root);
	return 0;
}
