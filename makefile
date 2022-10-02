lab1: lab1.c padre.o hijo.o
	gcc -o lab1 lab1.c padre.c hijo.c
		
padre.o: padre.c padre.h
	gcc -c padre.c

hijo.o: hijo.c hijo.h
	gcc -c hijo.c

clear:
	rm -f *.o main
