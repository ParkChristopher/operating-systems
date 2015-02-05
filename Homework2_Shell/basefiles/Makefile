all: prob1 prob2 prob3 prob4

prob1: cscd340lab4prob1.o utility.o linkedList.o
	gcc -o prob1 cscd340lab4prob1.o utility.o linkedList.o -lm

cscd340lab4prob1.o: cscd340lab4prob1.c utility.h
	gcc -ggdb -c -o cscd340lab4prob1.o cscd340lab4prob1.c

utility.o: utility.c utility.h
	gcc -ggdb -c -o utility.o utility.c

linkedList.o: linkedList.c linkedList.h utility.h
	gcc -ggdb -c -o linkedList.o linkedList.c

prob2: cscd340lab4prob2.c
	gcc -ggdb -o prob2 cscd340lab4prob2.c

prob3: cscd340lab4prob3.c
	gcc -ggdb -o prob3 cscd340lab4prob3.c

prob4: cscd340lab4prob4.c
	gcc -ggdb -o prob4 cscd340lab4prob4.c

clean:
	rm *.o *~
