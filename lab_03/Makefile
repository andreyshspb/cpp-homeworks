
CFLAGS = -I include -Wall -Wextra -Werror

lab_03: obj/main.o obj/clist.o 
	gcc $(CFLAGS) obj/main.o obj/clist.o -o lab_03

obj:
	mkdir obj


obj/main.o: src/main.c include/clist.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o


clean:
	rm -r obj
	rm lab_03
