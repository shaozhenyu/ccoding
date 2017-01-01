#include <stdio.h>

int isBadVersion(int version) {
	if (version >= 1702766719)
		return 1;
	return 0;
}

int badVersion(int start, int end) {
	printf("%d %d\n", start, end);
	if (start < 0 || end < 0)
		return 0;
	if (start == end)
		return start;
	int mid = start/2 + end/2;
	if (isBadVersion(mid)) {
		return badVersion(start, mid);
	} else {
		return badVersion(mid+1, end);
	}
	return 0;
}

int firstBadVersion(int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	if (isBadVersion(n/2)) {
		return badVersion(1, n/2);
	} else {
		return badVersion(n/2+1, n);
	}
	return 0;
}

int main() {
	printf("%d\n", firstBadVersion(2126753390));
}
