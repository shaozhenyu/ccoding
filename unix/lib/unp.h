#ifndef __unp_h
#define __unp_h

//#include "../config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

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

typedef void	Sigfunc(int);
Sigfunc *Signal(int, Sigfunc *);

const char	*Inet_ntop(int, const void *, char *, size_t);
void	Inet_pton(int, const char *, void *);

char	*Fgets(char *, int, FILE *);
void	Fputs(const char *, FILE *);

void	str_echo(int);
void	str_cli(FILE *, int);

ssize_t	Readline(int, void *, size_t);
void	Writen(int, void *, size_t);

int	Socket(int, int, int);
void	Bind(int, const SA *, socklen_t);
void Listen(int, int);
int	Accept(int, SA *, socklen_t *);
void	Connect(int, const SA *, socklen_t);

//void	err_dump(const char *, ...);
//void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);

#endif
