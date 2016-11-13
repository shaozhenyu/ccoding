#include <stdio.h>

int numTrees(int n) {
	if (n <= 0)
		return 0;
	int i, j, array[n+1];
	array[0] = 1;
	for (i = 1; i <= n; i++) {
		if (i <= 2)
			array[i] = i;
		else {
			array[i] = 0;
			for (j = 0; j < i; j++) {
				//printf("a b %d %d\n", array[j], array[i - j - 1]);
				array[i] += array[j] * array[i - j - 1];
			}
			//printf("nums : %d %d\n", array[i], i);
		}
	}
	return array[n];
}

int main() {
	printf("%d\n", numTrees(1));
	printf("%d\n", numTrees(2));
	printf("%d\n", numTrees(3));
	printf("%d\n", numTrees(4));
	printf("%d\n", numTrees(5));
	printf("%d\n", numTrees(6));
}
