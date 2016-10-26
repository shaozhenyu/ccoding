#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct TreeNode *createTree()
{
	int val;
	struct TreeNode *root = NULL; //must init, if not will result Segmentation fault
	scanf("%d", &val);

	if (val != 0) {
		root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
		root->val = val;
		root->left = NULL;
		root->right = NULL;

		root->left = createTree();
		root->right = createTree();
	}
	return root;
}
//root->left->right
void preOrderTraverse(struct TreeNode *root)
{
	struct TreeNode *p = root;
	if (p != NULL) {
		printf("%d ", p->val);
		preOrderTraverse(p->left);
		preOrderTraverse(p->right);
	}
}

//left->root->right
void inOrderTraverse(struct TreeNode *root)
{
	struct TreeNode *p = root;
	if (p != NULL) {
		inOrderTraverse(p->left);
		printf("%d ", p->val);
		inOrderTraverse(p->right);
	}
}

//left->right->root
void postOrderTraverse(struct TreeNode *root)
{
	struct TreeNode *p = root;
	if (p != NULL) {
		postOrderTraverse(p->left);
		postOrderTraverse(p->right);
		printf("%d ", p->val);
	}
}

void getLeftLeavesVal(struct TreeNode* root, int *sum) {
	struct TreeNode *p = root;
	if (p != NULL) {
		if (p->left != NULL) {
			if (p->left->left == NULL && p->left->right == NULL)
				*sum += p->left->val;
				return;
		}
		if (p->right != NULL) {
			getLeftLeavesVal(p->right, sum);
		}
	}
}

int sumOfLeftLeaves(struct TreeNode *root) {
	int sum = 0;

	getLeftLeavesVal(root, &sum);

	return sum;
}

int treeDeep(struct TreeNode *root) {
	int deep = 0;
	if (root) {
		int leftDeep = treeDeep(root->left);
		int rightDeep = treeDeep(root->right);
		deep = (leftDeep > rightDeep ? leftDeep : rightDeep) + 1;
		return deep;
	}
	return 0;
}

struct TreeNode* invertTree(struct TreeNode* root) {
	if (!root) {
		return NULL;
	}
	struct TreeNode *p = invertTree(root->left);
	root->left = invertTree(root->right);
	root->right = p;
	return root;
}

int main()
{
	struct TreeNode *root;
	root = createTree();

//	preOrderTraverse(root);
//	printf("\n");
//	inOrderTraverse(root);
//	printf("\n");
//	postOrderTraverse(root);
//	printf("\n");
//	printf("deep : %d\n", treeDeep(root));
//	int sum = sumOfLeftLeaves(root);
//	printf("%d\n", sum);
	struct TreeNode *p = invertTree(root);
	preOrderTraverse(root);
	printf("\n");
}
