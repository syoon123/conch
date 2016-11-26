GCC = gcc -g

all: shell.o
	$(GCC) shell.o -o prog

shell.o: shell.c shell.h
	$(GCC) -c shell.c

clean:
	rm *.o
	rm *~

run: all
	./prog

debug: all
	gdb prog
