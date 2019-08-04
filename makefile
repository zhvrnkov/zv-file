compile: main.o index.o flagsstruct.o
	gcc main.o index.o flagsstruct.o -o run.o

main.o: main.c
	gcc -c main.c

index.o: index.c
	gcc -c index.c

flagsstruct.o: flagsstruct.c
	gcc -c flagsstruct.c

run: 
	./run.o
