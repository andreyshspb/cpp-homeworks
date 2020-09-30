
CFLAGS = -I include -Wall -Wextra -Werror

lab1: bin/algorithm.o bin/io.o bin/main.o bin/util.o
	gcc $(CFLAGS) bin/algorithm.o bin/io.o bin/main.o bin/util.o -o lab1

all: lab1

bin:
	mkdir bin

bin/algorithm.o: src/algorithm.c include/max.h include/logDebug.h | bin
	gcc $(CFLAGS) -c src/algorithm.c -o bin/algorithm.o
	
bin/io.o: src/io.c | bin
	gcc $(CFLAGS) -c src/io.c -o bin/io.o
	
bin/main.o: src/main.c include/doComputation.h include/max.h include/logDebug.h | bin
	gcc $(CFLAGS) -c src/main.c -o bin/main.o
	
bin/util.o: src/util.c include/logDebug.h | bin
	gcc $(CFLAGS) -c src/util.c -o bin/util.o

clean:
	rm -r bin
	rm lab1
