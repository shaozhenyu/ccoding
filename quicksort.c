#include <stdio.h>


void quickSort(int a[], int low, int high) {
	if (low < high) {
		int i = low, j = high;
		int temp = a[i];
		while (i < j) {
			while (a[j] >= temp && i < j)
				j--;
			a[i] = a[j];
			while (a[i] <= temp && i < j)
				i++;
			a[j] = a[i];
		}
		a[i] = temp;
		quickSort(a, low, i-1);
		quickSort(a, j+1, high);
	}
}

int main() {
	int a[] = {5,1,2,9,0,7,6,8,4,3};
	quickSort(a, 0, 9);
	int i;
	for (i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");
}
