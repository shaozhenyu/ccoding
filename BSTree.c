#include <stdio.h>
#include <stdlib.h>

struct BSTree {
	int val;
	struct BSTree *left;
	struct BSTree *right;
};

void preOrderTraverse(struct BSTree *root)
{
	if (root) {
		printf("%d ", root->val);
		preOrderTraverse(root->left);
		preOrderTraverse(root->right);
	}
}

void inOrderTraverse(struct BSTree *root)
{
	if (root) {
		inOrderTraverse(root->left);
		printf("%d ", root->val);
		inOrderTraverse(root->right);
	}
}

//递归插入
struct BSTree* insertBST(struct BSTree *root, int val)
{
	if (root == NULL) {
		root = (struct BSTree *)malloc(sizeof(struct BSTree));
		if (!root)
			return NULL;
		root->val = val;
		root->left = root->right = NULL;
	} else {
		if (val == root->val) {
			return root;
		}
		if (val < root->val)
			root->left = insertBST(root->left, val);
		else
			root->right = insertBST(root->right, val);
	}
	return root;
}

//非递归插入
void insertBST1(struct BSTree *root, int val)
{
	struct BSTree *p;
	p = (struct BSTree *)malloc(sizeof(struct BSTree));
	if (!p)
		return;
	p->val = val;
	p->left = p->right = NULL;

	if (!root) {
		root = p;
	} else {
		struct BSTree *q = root;
		while (q->left != p && q->right != p) {
			if (val == q->val)
				return;
			if (val < q->val) {
				if (q->left)
					q = q->left;
				else
					q->left = p;
			} else {
				if (q->right) {
					q = q->right;
				}
				else
					q->right = p;
			}
		}
	}
}

struct BSTree *createBST(int a[], int len)
{
	struct BSTree *root = NULL;
	int i;
	for (i = 0; i < len; i++) {
		root = insertBST(root, a[i]);
	}

	return root;
}

int putVal(struct BSTree *root, int oldVal, int newVal)
{
	if (!root)
		return 0;
	
	if (oldVal < root->val)
		return putVal(root->left, oldVal, newVal);
	else if (oldVal > root->val)
		return putVal(root->right, oldVal, newVal);
	else
		root->val = newVal;
}

struct BSTree* min(struct BSTree *root)
{
	if (!root)
		return NULL;

	struct BSTree *p = root;

	while (p->left) {
		p = p->left;
	}
	return p;
}

struct BSTree* max(struct BSTree *root)
{
	if (!root)
		return NULL;

	struct BSTree *p = root;

	while (p->right) {
		p = p->right;
	}
	return p;
}

struct BSTree* deleteMin(struct BSTree *root)
{
	if (!root)
		return NULL;

	if (root->left == NULL)
		return root->right;
	else
		root->left = deleteMin(root->left);
	return root;
}

struct BSTree* deleteMax(struct BSTree *root)
{
	if (!root)
		return NULL;

	if (root->right == NULL)
		return root->left;
	else
		root->right = deleteMax(root->right);
	return root;
}

struct BSTree* delete(struct BSTree *root, int val)
{
	if (!root)
		return NULL;

	if (val < root->val)
		root->left = delete(root->left, val);
	else if (val > root->val)
		root->right = delete(root->right, val);
	else {
		if (root->left == NULL)
			return root->right;
		else if (root->right == NULL)
			return root->left;
		else {
			struct BSTree *p = root;
			root = min(p->right);
			root->right = deleteMin(p->right);
			root->left = p->left;
		}
	}
	return root;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {

	if (!root || !p || !q)
		return NULL;

	if (p->val <= root->val && q->val >= root->val)
		return root;
	if (p->val >= root->val && q->val <= root->val)
		return root;
	if (p->val <= root->val && q->val <= root->val && root->left)
		return lowestCommonAncestor(root->left, p, q);
	if (p->val >= root->val && q->val >= root->val && root->right)
		return lowestCommonAncestor(root->right, p, q);
	return NULL;
}

int main()
{
	int len = 10;
	int a[] = {4, 15, 18, 1, 13, 7, 2, 9, 0, 16};

	struct BSTree *root = createBST(a, 10);
	inOrderTraverse(root);
	printf("\n");
	//preOrderTraverse(root);
	//printf("\n");
	root = delete(root, 4);
	inOrderTraverse(root);
	printf("\n");
}
