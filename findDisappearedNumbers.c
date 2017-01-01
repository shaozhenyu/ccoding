#include <stdio.h>
#include <stdlib.h>

void quicksort(int a[],int low,int high)
{
	int i = low;
	int j = high;
	int temp = a[i];
	if (low < high){
		while (i < j){
			while (a[j] >= temp && i < j)
				j--;
			a[i] = a[j];
			while (a[i] <= temp && i < j)
				i++;
			a[j] = a[i];
		}
		a[i] = temp;
		quicksort(a,low,i-1);
		quicksort(a,j+1,high);
	}
}

int* findDuplicates(int* nums, int numsSize, int* returnSize) {
	int i, j = 1;
	int len = 0, flag = 0;
	int *a = (int *)malloc(sizeof(int) * numsSize);
	quicksort(nums, 0, numsSize-1);
	for (i = 0; i < numsSize; ) {
		if (j == nums[i]) {
			if (flag == 1) {
				a[len++] = j;
				flag = 0;
			} else {
				flag = 1;
			}
			i++;
		} else if (j < nums[i]) {
			j++;
			flag = 0;
		} else if (j > nums[i]) {
			i++;
			flag = 0;
		}
	}
	*returnSize = len;
	return a;
}

int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
	int i, j = 1;
	int *a = NULL;
	int len = 0;
	quicksort(nums, 0, numsSize-1);
	a = (int *)malloc(sizeof(int) * 1000);
	for (i = 0; i < numsSize; ) {
		if (j == nums[i]) {
			j++;
			i++;
		} else if (j < nums[i]) {
			a[len++] = j;
			j++;
		} else if (j > nums[i]) {
			i++;
		}
	}

	while (j <= numsSize) {
		a[len++] = j;
		j++;
	}

	*returnSize = len;
	return a;
}

int main() {
	int i;
	int a[] = {4,3,2,3,3,2,3,1};
	int size = 0;
	int *b = findDuplicates(a, 8, &size);
	printf("%d\n", size);
	for (i = 0; i < size; i++) {
		printf("%d\n", *b);
		b++;
	}
}
