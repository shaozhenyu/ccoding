#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int pathSum1(struct TreeNode* root, int sum, int origin, int flag) {
	if (!root)
		return 0;
	int count = 0;
	if (root->val == sum) {
		count = 1 + pathSum1(root->left, 0, origin, 1) + pathSum1(root->right, 0, origin, 1);
	} else {
		int next = sum - root->val;
		count =  pathSum1(root->left, next, origin, 1) + pathSum1(root->right, next, origin, 1);
	}

	//从下一个节点开始新的计算，如果不设置flag， 会导致二次计算
    if (flag == 0)
	    count += pathSum1(root->left, origin, origin, 0) + pathSum1(root->right, origin, origin, 0);
	return count;
}

int pathSum(struct TreeNode* root, int sum) {
	return pathSum1(root, sum, sum, 0);
}

int isMirror(struct TreeNode* left, struct TreeNode* right) {

	if (!left && !right) {
		return 1;
	}

	if ((!left && right) || (left && !right)) {
		return 0;
	}

	if (left->val != right->val)
		return 0;

	return isMirror(left->left, right->right) & isMirror(left->right, right->left);
}

int isSymmetric(struct TreeNode* root) {
	if (!root) {
		return 1;
	}

	return isMirror(root->left, root->right);
}

int treeSize(struct TreeNode *root) {
	if (!root)
		return 0;
	return (treeSize(root->left) + treeSize(root->right) + 1);
}

int buffSize = 0;
void push(int val, int *buf) {
	buf[buffSize++] = val;
}

void inorder(struct TreeNode *root, int* buf) {
	if (root) {
		inorder(root->left, buf);
		push(root->val, buf);
		inorder(root->right, buf);
	}
}

void preorder(struct TreeNode *root, int* buf) {
	if (root) {
		push(root->val, buf);
		inorder(root->left, buf);
		inorder(root->right, buf);
	}
}

int* orderTraversal(struct TreeNode* root, int* returnSize) {
	int size = treeSize(root);
	buffSize = 0;
	*returnSize = size;

	int *buff = (int *)malloc(sizeof(int) * size);
	if (!buff)
		return 0;
	inorder(root, buff);
	return buff;
}

int treeDeepBalanced(struct TreeNode* root) {
	int leftDeep, rightDeep;
	if (root) {
		leftDeep = treeDeepBalanced(root->left);
		rightDeep = treeDeepBalanced(root->right);
		if (leftDeep == -1 || rightDeep == -1)
			return -1;
		int h = leftDeep - rightDeep;
		if (h > 1 || h < -1) {
			return -1;
		} else {
			return (leftDeep > rightDeep ? leftDeep : rightDeep) + 1;
		}
	}
	return 0;
}

int isBalanced(struct TreeNode* root) {
	int leftDeep, rightDeep;
	if (root) {
		leftDeep = treeDeepBalanced(root->left);
		rightDeep = treeDeepBalanced(root->right);
		if (leftDeep == -1 || rightDeep == -1)
			return 0;
		int h = leftDeep - rightDeep;
		if (h <= 1 && h >= -1)
			return 1;
		else
			return 0;
	}
	return 1;
}

/*
bool isBalanced(struct TreeNode* root) {
	int leftDeep, rightDeep;
	if (root) {
		leftDeep = treeDeep(root->left);
		rightDeep = treeDeep(root->right);
		int h = leftDeep - rightDeep;
		if (h <= 1 && h >= -1)
			return isBalanced(root->left) && isBalanced(root->right);
		else
			return false;
	}
	return true;
}
*/

int bufSize;
int nullNodeSize(struct TreeNode *root) {
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return 1;
	else
		return nullNodeSize(root->left) + nullNodeSize(root->right);
	return 0;
}

void writeBuff(struct TreeNode* root, char** buf, int size, int flag) {
	if (root) {
		if (flag != 0) {
			sprintf(buf[size], "%s->%d", buf[size], root->val);
			printf("%s ---%d --- %d \n", buf[size], root->val, size);
		}
		if (root->left && root->right) {
			buf[size+1] = buf[size];
			printf("111 %s %s \n", buf[size], buf[size+1]);
			writeBuff(root->left, buf, size, 1);
			writeBuff(root->right, buf, size+1, 1);
		} else if (root->left && !root->right) {
			writeBuff(root->left, buf, size, 1);
		} else if (root->right && !root->left) {
			writeBuff(root->right, buf, size, 1);
		}
	}
}

char** binaryTreePaths(struct TreeNode* root, int *returnSize) {
	if (root) {
		int size = nullNodeSize(root);
		*returnSize = size;
		char **buf = (char **)malloc(size * sizeof(char *));
		if (!buf)
			return NULL;
		char *string;
		sprintf(string, "%d", root->val);
		//printf("%s-----\n", buf[0]);
		buf[0] = string;
		writeBuff(root, buf, 0, 0);
		int i;
		printf("----- %d\n", *returnSize);
		for (i = 0; i < *returnSize; i++) {
			printf("%s\n", buf[i]);
		}
		printf("\n");
		return buf;
	}
	return NULL;
}

int main()
{
	struct TreeNode *root;
	root = createTree();
	int i, size = 0;
	char **buf = binaryTreePaths(root, &size);
	printf("222222222 : %d\n", size);
	printf("%s\n", buf[0]);
	printf("%s\n", buf[1]);
	for (i = 0; i < size; i++) {
		printf("%s\n", buf[i]);
	}
	printf("\n");
}
