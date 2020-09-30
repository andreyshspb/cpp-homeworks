
CFLAGS = -I include -Wall -Wextra -Werror 

lab_04: obj/main.o obj/mergesort.o 
	gcc $(CFLAGS) obj/main.o obj/mergesort.o -o lab_04

obj:
	mkdir obj


obj/main.o: src/main.c include/mergesort.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/mergesort.o: src/mergesort.c | obj
	gcc $(CFLAGS) -c src/mergesort.c -o obj/mergesort.o


clean:
	rm -r obj
	rm lab_04
