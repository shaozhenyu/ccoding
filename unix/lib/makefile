CC = gcc
CFLAGS = -g -Wall

SRC = ${wildcard *.c}
OBJ = ${patsubst %.c, %.o, $(SRC)}

all : $(OBJ)

$(OBJ): %.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm *.o
