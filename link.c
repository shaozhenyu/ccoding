#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* create(int a[], int len) {
	int i = 0;
	struct ListNode *h, *p, *r;

	r = p = h = NULL;

	for (; i < len; i++) {
		p = (struct ListNode *)malloc(sizeof(struct ListNode));
		if (!p) {
			return NULL;
		}
		p->val = a[i];
		p->next = NULL;
		if (NULL == h) {
			h = p;
		} else {
			r->next = p;
		}
		r = p;
	}
	return h;
}

int listLen(struct ListNode *h) {
	int i = 0;
	struct ListNode *p = h;

	while (p) {
		i++;
		p = p->next;
	}
	return i;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode *p1, *p2;
	int i = 0;
	int len, len1, len2;

	int a[1000000];

	len1 = listLen(l1);
	len2 = listLen(l2);
	if (len1 < len2) {
		len = len1;
		len1 = len2;
		len2 = len;

		p1 = l2;
		p2 = l1;
	} else {
		p1 = l1;
		p2 = l2;
	}

	int add = 0;
	int s = 0;
	for (i = 0; i < len2; i++) {
		if (p1 == NULL || p2 == NULL) {
			break;
		}
		s = p1->val + p2->val;

		a[i] = s%10 + add;
		if (a[i] >= 10) {
			a[i] = a[i]%10;
		}
		printf("%d %d %d\n", a[i], s, add);
		if ((s+add) >= 10) {
			add = 1;
		} else {
			add = 0;
		}

		p1 = p1->next;
		p2 = p2->next;
	}

	while (p1) {
		a[i] = (p1->val + add)%10;
		if ((p1->val + add) >= 10) {
			add = 1;
		} else {
			add = 0;
		}
		p1 = p1->next;
		i++;
	}

	if (add == 1) {
		a[i] = 1;
		len1 += 1;
	}

	struct ListNode *h = create(a, len1);
	return h;
}

void printList(struct ListNode *h) {
	struct ListNode *p = h;

	while (p) {
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}

struct ListNode* swapPairs(struct ListNode* head) {
	struct ListNode *p = head;
	struct ListNode *r, *q;

	int len = listLen(head);

	if (len == 0) {
		return NULL;
	}
	if (len == 1) {
		return head;
	}

	q = p->next;

	if (len == 2) {
		q->next = p;
		p->next = NULL;
		return q;
	}

	int i = 0;
	for (; i < len/2; i++) {
		if (i == 0) {
			r = q;
			p->next = q->next;
			q->next = p;
			head = q;
		} else {
			if (q->next == NULL) {
				r->next = q;
				q->next = p;
				p->next = NULL;
				return head;
			} else {
				p->next = q->next;
				r->next = q;
				q->next = p;
			}
		}

		r = p;
		p = p->next;
		if (p->next == NULL) {
			return head;
		}
		q = p->next;
	}

	return head;
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode *p, *head;

	struct ListNode *p1, *p2;
	p1 = l1;
	p2 = l2;

	if (p1 == NULL && p2 == NULL) {
		return NULL;
	}

	if (p1 == NULL) {
		return p2;
	}

	if (p2 == NULL) {
		return p1;
	}

	head = NULL;
	while (p1 && p2) {
		if (p1->val <=  p2->val) {
			if (head == NULL) {
				head = p1;
				p = head;
			} else {
				p->next = p1;
				p = p->next;
			}
			p1 = p1->next;
		} else {
			if (head == NULL) {
				head = p2;
				p = head;
			} else {
				p->next = p2;
				p = p->next;
			}
			p2 = p2->next;
		}
	}

	while (p1) {
		p->next = p1;
		p = p->next;
		p1 = p1->next;
	}

	while (p2) {
		p->next = p2;
		p = p->next;
		p2 = p2->next;
	}

	p->next = NULL;
	return head;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
	struct ListNode *p, *q, *r;

	r = p = q = head;

	if (p == NULL) {
		return NULL;
	}

	if (p->next == NULL) {
		return head;
	}

	int before = p->val;
	p = p->next;
	q = p->next;
	while (p) {
		if (p->val == before) {
			if (q == NULL) {
				r->next = NULL;
				return head;
			} else {
				r->next = q;
				p = q;
				q = p->next;
			}
		} else {
			if (q == NULL) {
				return head;
			} else {
				r = p;
				p = q;
				q = p->next;
				before = r->val;
			}
		}
	}

	return head;
}

struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
	struct ListNode *p, *r;
	if (head == NULL) {
		return NULL;
	}

	int a[100000];

	if (head->next == NULL || m == n) {
		return head;
	}

	p = head;
	int len;
	int i = 0, j, temp;

	while (p) {
		a[i] = p->val;
		i++;
		p = p->next;
	}

	len = i;

	for (i = m-1, j = n-1; i < j; i++, j--) {
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

	r = create(a, len);

	return r;
}
struct ListNode* reverseTwo(struct ListNode* head, int m, int n) {
	struct ListNode *p = head;

	if (head == NULL) {
		return NULL;
	}

	if (head->next == NULL) {
		return head;
	}

	int mm, nn;

	if (m == n) {
		return head;
	}

	int len = 1;
	while (p) {
		if (len == m) {
			nn = p->val;
		}
		if (len == n) {
			mm = p->val;
			break;
		}
		len++;
		p = p->next;
	}

	struct ListNode *r, *q;
	r = p = head;
	q = p->next;

	len = 1;
	while (p) {
		if (len == m) {
			struct ListNode *this = (struct ListNode *)malloc(sizeof(struct ListNode));
			if (!this) {
				return NULL;
			}
			this->val = mm;
			this->next = NULL;

			if (p == head) {
				head = this;
				this->next = q;
			} else if (q == NULL) {
				return NULL;
			} else {
				r->next = this;
				this->next = q;
			}
			p = this;
		}
		if (len == n) {
			struct ListNode *this = (struct ListNode *)malloc(sizeof(struct ListNode));
			if (!this) {
				return NULL;
			}
			this->val = nn;
			this->next = NULL;

			if (q == NULL) {
				r->next = this;
				return head;
			} else {
				r->next = this;
				this->next = q;
				p->next = NULL;
				p->val = 0;
				return head;
			}
		}
		r = p;
		p = q;
		q = p->next;
		len++;
	}

	printList(head);

	return head;
}

struct ListNode* partition(struct ListNode* head, int x) {
	struct ListNode *p, *r, *q;
	if (head == NULL) {
		return NULL;
	}
	if (head->next == NULL) {
		return head;
	}

	r = p = head;
	q = p->next;

	while (p != NULL && p->val < x) {
		if (q == NULL) {
			return head;
		}
		r = p;
		p = p->next;
		q = p->next;
	}

	if (p == NULL) {
		return head;
	}

	struct ListNode *tp, *tr, *tq;
	tp = p;
	tr = r;
	tq = q;

	while (tp != NULL) {
		if (tp->val < x) {
			if (r->val >= x) {
				tr->next = tq;
				tp->next = r;
				head = tp;
			} else {
				tp->next = r->next;
				r->next = tp;
				tr->next = tq;
			}
			r = tp;

			if (tq == NULL) {
				return head;
			} else {
				tp = tq;
				tq = tq->next;
			}
		} else {
			if (tq == NULL) {
				return head;
			} else {
				tr = tp;
				tp = tq;
				tq = tq->next;
			}
		}
	}

	return head;
}

struct ListNode* reverseList(struct ListNode* head) {

	if (head == NULL) {
		return NULL;
	}
	if (head->next == NULL) {
		return head;
	}

	struct ListNode *r, *p, *q;

	r = head;
	p = head->next;
	q = p->next;

	while (p) {
		if (q == NULL) {
			p->next = head;
			r->next = NULL;
			return p;
		} else {
			p->next = head;
			head = p;
			r->next = q;
			p = q;
			q = q->next;
		}
	}

	return NULL;
}

int hasCycle(struct ListNode *head) {
	if (head == NULL) {
		return 0;
	}

	struct ListNode *p, *q;

	p = head;
	q = p->next;

	while (p && q) {
		if (p == q)
			return 1;
		p = p->next;
		q = q->next;
		if (q == NULL) {
			return 0;
		} else {
			q = q->next;
		}
	}
	return 0;
}

int main() {
	struct ListNode *l1, *l2, *l;
	int a[] = {1, 1};
	l1 = create(a, 2);
	int b[] = {1, 2};
	l2 = create(b, 2);
	//	l = addTwoNumbers(l1, l2);
	//	int a[] = {1, 2, 3, 4, 5, 6};
	//	l1 = create(a, 6);
	//	l = swapPairs(l1);

	//l = mergeTwoLists(l1, l2);

	//l = deleteDuplicates(l2);
	//l = reverseBetween(l1, 2, 4);
	//l = partition(l1, 2);
	//l = reverseList(l2);
	//printList(l);
	int flag = hasCycle(l2);
	printf("%d\n", flag);


	return 0;
}
