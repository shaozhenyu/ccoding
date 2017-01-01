#include <stdio.h>
#include <stdlib.h>

struct BSTree {
	int val;
	int times;
	struct BSTree *left;
	struct BSTree *right;
};

struct BSTree *insertBST(struct BSTree *root, int num) {
	if (root == NULL) {
		root = (struct BSTree *)malloc(sizeof(struct BSTree));
		if (!root)
			return NULL;
		root->val = num;
		root->times = 1;
		root->left = root->right = NULL;
	} else {
		if (root->val == num)
			root->times += 1;
		else if (root->val > num)
			root->left = insertBST(root->left, num);
		else
			root->right = insertBST(root->right, num);
	}
	return root;
}

struct BSTree *createBST(int nums[], int len) {
	struct BSTree *root = NULL;
	int i;
	for (i = 0; i < len; i++) {
		printf("111 %d\n", nums[i]);
		root = insertBST(root, nums[i]);
	}
	return root;
}

void preFindSingleNumber(struct BSTree *root, int *returnSize) {
	if (root) {
		if (root->times == 1) {
			printf("222 %d\n", root->val);
			*returnSize = root->val;
			returnSize++;
		}
		preFindSingleNumber(root->left, returnSize);
		preFindSingleNumber(root->right, returnSize);
	}
}

int* singleNumber(int* nums, int numsSize, int* returnSize) {
	struct BSTree *root = createBST(nums, numsSize);
	int *p = (int *)malloc(sizeof(int) * 2);
	preFindSingleNumber(root, returnSize);
	p[0] = 1;
	p[1] = 2;
	return p;
}

int main() {
	//int a[] = {1, 1, 2, 0, 3, 5, 3, 0};
	//214748647
	//[160988123,1063150409]
	int a[] = {-1638685546,-2084083624,-307525016,-930251592,-1638685546,1354460680,623522045,-1370026032,-307525016,-2084083624,-930251592,472570145,-1370026032,1063150409,160988123,1122167217,1145305475,472570145,623522045,1122167217,1354460680,1145305475};
	int returnSize[2];
	int *p;
	p = singleNumber(a, 22, returnSize);
	printf("\n");
	int i;
	for (i = 0; i < 2; i++) {
		printf("%d ", returnSize[i]);
	}
	printf("\n");
	//struct BSTree *root = createBST(a, 8);
	//printBST(root);
}
