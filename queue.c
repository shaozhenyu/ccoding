#include <stdio.h>
#include <stdlib.h>

struct QNode {
	int val;
	struct QNode *next;
};

struct Queue {
	struct QNode *front;
	struct QNode *rear;
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

void enqueue(struct Queue *q, int key) {
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

void dequeue(struct Queue *q, int *val) {
	if (!q)
		return;
	if (q->front == q->rear)
		return;
	struct QNode *p = q->front->next;
	*val = p->val;
	q->front->next = p->next;
	if (q->rear == p) {
		q->rear = q->front;
	}
	free(p);
}

void queueTraverse(struct Queue *q) {
	if (!q)
		return;
	struct QNode *p = q->front->next;
	while (p) {
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}

int main() {
	int val;
	struct Queue *q = initQueue();
	if (q == NULL) {
		printf("init error!\n");
		return 0;
	}
	enqueue(q, 10);
	enqueue(q, 11);
	enqueue(q, 12);
	dequeue(q, &val);
	queueTraverse(q);
	return 0;
}
