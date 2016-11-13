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

int* rightSideView(struct TreeNode* root, int* returnSize) {
	if (!root)
		return NULL;
	int* ret = (int *)malloc(sizeof(int) * 1000);
	if (!ret)
		return NULL;
	struct TreeNode *queue[1000] = {0};
	int first = 0, end = 0;
	int parent = 1, child = 0;
	int level = 0;
	
	queue[end++] = root;
	while (first < end) {
		struct TreeNode *tmp = queue[first++];
		if (tmp->left) {
			queue[end++] = tmp->left;
			child++;
		}
		if (tmp->right) {
			queue[end++] = tmp->right;
			child++;
		}
		parent--;
		if (parent == 0) {
			ret[level++] = tmp->val;
			parent = child;
			child = 0;
		}
	}
	*returnSize = level;
	return ret;
}

int main() {
	//create tree
	struct TreeNode t[9] = {0};
	int i, j;
	for (i = 0; i < 9; i++)
		t[i].val = i;
	
	linkTreeNode(t, 1, 2, 3);
	linkTreeNode(t, 2, 4, 5);
	linkTreeNode(t, 3, -1, 6);
	linkTreeNode(t, 5, 7, 8);

	int size;
	int *a = rightSideView(&t[1], &size);
	for (i = 0; i < size; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
