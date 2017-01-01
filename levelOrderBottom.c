#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

void linkTreeNode(struct TreeNode *t, int parent, int left, int right) {
	if (left != -1)
		t[parent].left = &t[left];
	if (right != -1)
		t[parent].right = &t[right];
}

int deepTree(struct TreeNode *root) {
	if (!root)
		return 0;
	return 1 + (deepTree(root->left) > deepTree(root->right) ? deepTree(root->left) : deepTree(root->right));
}

int maxDepthTree (struct TreeNode* root)
{
	if (!root)
		return 0;
	int DepthL = maxDepthTree(root->left) + 1;
	int DepthR = maxDepthTree(root->right) + 1;
	return (DepthL > DepthR ? DepthL : DepthR);
}

int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
	if (!root)
		return NULL;
	int i, j;
	int level = maxDepthTree(root);
	//int level = deepTree(root);
	*returnSize = level;
	*columnSizes = (int *)malloc(sizeof(int) * (level+1));
	int** ret = (int **)malloc(sizeof(int*) * (level+1));

	printf("level :%d\n", level);

	for (i = 0; i < level; i++)
		ret[i] = (int *)malloc(sizeof(int) * 1000);

	struct TreeNode *queue[1000] = {0};
	struct TreeNode *now = NULL;
	int parent = 1, child = 0;
	int first = 0, end = 0;
	i = j = 0;
	queue[end++] = root;
	while (first < end) {
		now = queue[first++];
		ret[level-i-1][j++] = now->val;
		if (now->left) {
			queue[end++] = now->left;
			child++;
		}
		if (now->right) {
			queue[end++] = now->right;
			child++;
		}
		parent--;
		if (parent == 0) {
			(*columnSizes)[level-i-1] = j;
			i++;
			j = 0;
			parent = child;
			child = 0;
		}
	}

	return ret;
}

int main() {
	//create tree
	struct TreeNode t[9] = {0};
	int i, j;
	for (i = 0; i < 6; i++)
		t[i].val = i;

	linkTreeNode(t, 1, 2, 3);
	//linkTreeNode(t, 2, 4, 5);
	linkTreeNode(t, 3, 4, 5);
	//linkTreeNode(t, 5, 7, 8);

	//printNodeByLevel(&t[1]);
	printf("sequeue : \n");
	int *a;
	int b;
	int **arr = levelOrderBottom(&t[1], &a, &b);
	printf("11 %d\n", a[2]);
	for (i = 0; i < b; i++) {
		printf("%d\n", a[i]);
	}
	for (i = 0; i < b; i++) {
		for (j = 0; j < a[i]; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	return 0;
}
