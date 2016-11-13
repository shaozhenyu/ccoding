#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 10
#define STACK_INCREASE 2

struct Stack {
	int *base;
	int *top;
	int stackSize;
};

struct Stack *stackInit() {
	struct Stack *st;
	st->base = (int *)malloc(sizeof(int) * STACK_INIT_SIZE);
	if (st->base == NULL) {
		return NULL;
	}
	st->top = st->base;
	st->stackSize = STACK_INIT_SIZE;
	return st;
}

struct Stack *push(struct Stack *st, int key) {
	if (st == NULL)
		return NULL;
	if ((st->top - st->base) >= st->stackSize) {
		st->base = (int *)realloc(st->base, st->stackSize + STACK_INCREASE);
		if (!st->base)
			return NULL;
		st->top = st->base + st->stackSize;
		st->stackSize += STACK_INCREASE;
	}
	*(st->top++) = key;
	return st;
}

int pop(struct Stack *st, int *key) {
	if (st == NULL)
		return 0;
	if (st->base == st->top)
		return 0;
	//printf("%d ss\n", *(--st->top));
	*key = *(--st->top);
	return 1;
}

int stackLen(struct Stack *st) {
	return st->top - st->base;
}

void destoryStack(struct Stack *st) {
	free(st->base);
	st->base = st->top = NULL;
	st->stackSize = 0;
}

struct Stack *clearStack(struct Stack *st) {
	st->top = st->base;
	return st;
}

void stackTraverse(struct Stack *st) {
	if (!st)
		return;
	while (st->base != st->top) {
		printf("%d ", *(st->base)++);
	}
	printf("\n");
}

int main() {
	int i;
	int val;
	struct Stack *st = stackInit();
	for (i = 0; i < 15; i++)
		st = push(st, i);

	pop(st, &val);
	//printf("val : %d\n", val);

	printf("len : %d\n", stackLen(st));
	stackTraverse(st);
}
