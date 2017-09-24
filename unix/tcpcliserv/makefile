CC = gcc
CFLAGS = -g -Wall

LIB = ../lib/

SRC = ${wildcard *.c}
OBJ = ${patsubst %.c, %.o, $(SRC)}

all: $(OBJ) tcpserv01 tcpcli01

tcpserv01: tcpserv01.o $(LIB)str_echo.o $(LIB)writen.o $(LIB)error.o $(LIB)wrapsock.o
	$(CC) -o $@ $^

tcpserv03: tcpserv03.o $(LIB)str_echo.o $(LIB)writen.o $(LIB)error.o $(LIB)wrapsock.o sigchldwait.o $(LIB)signal.o
	$(CC) -o $@ $^

tcpcli01: tcpcli01.o $(LIB)str_cli.o $(LIB)readline.o $(LIB)error.o $(LIB)wrapsock.o $(LIB)wrapstdio.o $(LIB)wraplib.o $(LIB)writen.o

tcpcli04: tcpcli04.o $(LIB)str_cli.o $(LIB)readline.o $(LIB)error.o $(LIB)wrapsock.o $(LIB)wrapstdio.o $(LIB)wraplib.o $(LIB)writen.o

$(OBJ): %.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@


#tcpserv01.o:
#	$(CC) -c -o tcpserv01.o tcpserv01.c

clean:
	rm -rf *.o tcpserv01 tcpserv03 tcpcli01 tcpcli04
