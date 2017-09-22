CC = gcc

tcpserv01: tcpserv01.o ../lib/str_echo.o ../lib/writen.o
	$(CC) -o $@ $^
../lib/str_echo.o: ../lib/str_echo.c
	$(CC) -c -o $@ $^
../lib/writen.o: ../lib/writen.c
	$(CC) -c -o $@ $^

tcpserv01.o:
	$(CC) -c -o tcpserv01.o tcpserv01.c

clean:
	rm *.o
