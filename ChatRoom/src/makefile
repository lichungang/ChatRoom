BIN_DIR=../bin
INCLUDE_FLAG=-I ../include -I./
LIB_DIR=../lib

server : server.o Connect.o
	gcc -o $@ $^ -g -pthread
clinet : client.o Connect.o
	gcc -o $@ $^ -g -pthread
%.o:%.c
	gcc -o $@ ${INCLUDE_FLAG} -c $^
