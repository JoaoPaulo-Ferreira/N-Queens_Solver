# CFLAGS=-Wall -std=c++14 -pedantic
CC=gcc
SRC=src/
IPATH=-I inc/
OBJ=obj/
BIN=bin/
minisat := $(shell command -v minisat 2> /dev/null)


all:	fndAnsw.o main.o 

ifndef minisat
    $(error "minisat is not available.	Please try: sudo apt install minisat" )
endif
	${CC} -o ${BIN}App ${OBJ}main.o ${OBJ}fndAnsw.o

fndAnsw.o:
	${CC} ${IPATH} -c ${SRC}fndAnsw.c -o ${OBJ}fndAnsw.o -lm

main.o: 
	${CC} ${IPATH} -c ${SRC}main.c -o ${OBJ}main.o -ld	


run:
	clear
	@${BIN}App

clean: 
	rm $(OBJ)*.o
	rm ${BIN}App

full: clean all run
