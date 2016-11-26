GCC = gcc -g

all: shell.o main.o
	$(GCC) main.o shell.o -o prog

main.o: main.c shell.c
	$(GCC) -c main.c

shell.o: shell.c shell.h
	$(GCC) -c shell.c

clean:
	rm *.o
	rm *~

run: all
	./prog

debug: all
	gdb prog
