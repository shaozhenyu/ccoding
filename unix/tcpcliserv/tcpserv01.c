#include <stdio.h>

#include "../lib/unp.h"

int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) {
		printf("socket error!");
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) < 0) {
		printf("bind error");
		return -1;
	}

	if (listen(listenfd, LISTENQ) < 0) {
		printf("listen error");
		return -1;
	}

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *)&cliaddr, &clilen);

		if ((childpid = fork()) == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}

		close(connfd);
	}
}

