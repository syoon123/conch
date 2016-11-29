GCC = gcc -g

all: shell.o main.o parse.o
	$(GCC) main.o shell.o parse.o -o prog

main.o: main.c shell.c parse.c
	$(GCC) -c main.c

shell.o: shell.c shell.h
	$(GCC) -c shell.c

parse.o: parse.c parse.h
	$(GCC) -c parse.c

clean:
	rm *.o
	rm *~

run: all
	./prog

debug: all
	gdb prog
