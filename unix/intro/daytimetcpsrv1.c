#include "../lib/unp.h"
#include <time.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int n;
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
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

	for ( ; ; ) {
		len = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (SA *)&cliaddr, &len)) < 0) {
			printf("accept error");
			return 0;
		}
		printf("connectopn from %s, port %d\n",
				inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)), ntohs(cliaddr.sin_port));

		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		write(connfd, buf, strlen(buf));

		close(connfd);
	}
}
