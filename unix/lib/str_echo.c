#include <stdio.h>

#include "unp.h"

/*
ssize_t writen(int fd, const void *vptr, size_t n){
{
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return 0;
}
*/

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while ((n = read(sockfd, buf, MAXLINE)) > 0)
		writen(sockfd, buf, n);

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0) {
		printf("read error");
		return;
	}
}
