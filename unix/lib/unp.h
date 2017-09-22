#ifndef __unp_h
#define __unp_h

//#include "../config.h"
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define LISTENQ 1024
#define MAXLINE 4090
#define BUFFSIZE 8192

#define SA struct sockaddr

#define SERV_PORT 9877
#define SERV_PORT_STR "9877"

void	str_echo(int);
ssize_t	writen(int, const void *, size_t);

#endif
