#include <stdio.h>
#include <stdlib.h>

struct QNode {
	struct TreeNode *val;
	struct QNode *next;
};

struct Queue {
	struct QNode *front;
	struct QNode *rear;
};

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct Queue *initQueue() {
	struct Queue *q;
	q = (struct Queue *)malloc(sizeof(struct Queue));
	if (!q)
		return NULL;
	q->front = q->rear = (struct QNode *)malloc(sizeof(struct QNode));
	if (!q->front || !q->rear)
		return NULL;
	q->front->next = NULL;
	return q;
}

void enqueue(struct Queue *q, struct TreeNode *key) {
	if (!q)
		return;
	struct QNode *p = (struct QNode *)malloc(sizeof(struct QNode));
	if (!p)
		return;
	p->val = key;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}

int isEmpty(struct Queue *q) {
	return ((q->rear == q->front) ? 1 : 0);
}

struct TreeNode* dequeue(struct Queue *q) {
	if (!q)
		return NULL;
	if (q->front == q->rear)
		return NULL;
	struct QNode *p = q->front->next;
	q->front->next = p->next;
	if (q->rear == p) {
		q->rear = q->front;
	}
	return p->val;
}

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

int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
	int i, j;
	struct Queue *q = initQueue();
	if (!q)
		return NULL;
	if (!root)
		return NULL;
	int level = deepTree(root);//not fast, but save space
	*returnSize = level;
	*columnSizes = (int *)malloc(sizeof(int) * 1000);
	if (!columnSizes)
		return NULL;

	int** ret = (int **)malloc(sizeof(int*) * 1000);
	if (!ret)
		return NULL;

	struct TreeNode *now = NULL;
	enqueue(q, root);
	int parent = 1;
	int child = 0;
	i = j = 0;
	ret[level-i-1] = (int *)malloc(sizeof(int) * 1000);
	if (!ret)
		return NULL;
	while (!isEmpty(q)) {
		now = dequeue(q);
		ret[level-i-1][j++] = now->val;
		//printf("%d ", now->val);
		if (now->left) {
			enqueue(q, now->left);
			child++;
		}
		if (now->right) {
			enqueue(q, now->right);
			child++;
		}
		parent--;
		if (parent == 0) {
			(*columnSizes)[level-i-1] = j;
			i++;
			j = 0;
			parent = child;
			ret[level-i-1] = (int *)malloc(sizeof(int) * 1000);
			if (!ret)
				return NULL;
			child = 0;
		}
	}

	return ret;
}

void printNodeByLevel(struct TreeNode *root) {
	struct Queue *q = initQueue();
	if (!q) {
		printf("init queue error!\n");
		return;
	}
	struct TreeNode *now = NULL;
	enqueue(q, root);
	while (!isEmpty(q)) {
		now = dequeue(q);
		printf("%d ", now->val);
		if (now->left)
			enqueue(q, now->left);
		if (now->right)
			enqueue(q, now->right);
	}
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
	int **arr = levelOrder(&t[1], &a, &b);
	for (i = 0; i < b; i++) {
		for (j = 0; j < a[i]; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	return 0;
}
