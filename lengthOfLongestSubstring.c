#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
	int i, j, k;
	int len = 1;
	int max = 1;

	if (strlen(s) == 0) {
	    return 0;
	}

	for (i = 0; i < strlen(s)-1; i++) {
		len = 1;
		for (j = i + 1; j < strlen(s); j++) {
			printf("%d ", j);
			for (k = i; k < j; k++) {
				if (s[k] == s[j]) {
					if (max < len) {
						max = len;
					}
					j = 0;
				}
			}

			if (j == 0) {
				break;
			}
			printf("%c\n", s[j]);
			len += 1;
		}
		if (len > max) {
			max = len;
		}
	}

	return max;
}

int main() {
	char* s = "abcabcbb";
	int len = lengthOfLongestSubstring(s);
	printf("\n");
	printf("%d\n", len);
}
