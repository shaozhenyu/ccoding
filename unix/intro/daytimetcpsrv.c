#include "../lib/unp.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sockfd_to_family(int sockfd) {
	struct sockaddr_storage ss;
	socklen_t len;

	len = sizeof(ss);
	if (getsockname(sockfd, (SA *) &ss, &len) < 0) {
		return -1;
	}
	printf("family :%hhu\n", ss.ss_family);
	printf("addr :%hhu\n", ss.sin_addr);
	return 0;
}

int main(int argc, char **argv)
{
	int n;
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	time_t ticks;

	memset(&servaddr, 0, sizeof(SA));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(13);

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket error");
		return 0;
	}

	if ((n = bind(listenfd, (SA *)&servaddr, sizeof(SA))) < 0) {
		printf("bind error %d\n", n);
		return 0;
	}

	listen(listenfd, LISTENQ);

	sockfd_to_family(listenfd);

	for ( ; ; ) {
		if ((connfd = accept(listenfd, (SA *)NULL, NULL)) < 0) {
			printf("accept error");
			return 0;
		}
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		write(connfd, buf, strlen(buf));

		close(connfd);
	}
}
