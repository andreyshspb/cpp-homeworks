
CFLAGS = -I include -Wall -Wextra -Werror

lab_02: obj/str.o obj/test.o obj/test_str.o
	gcc $(CFLAGS) obj/str.o obj/test.o obj/test_str.o -o lab_02

obj:
	mkdir obj


obj/str.o: src/str.c | obj
	gcc $(CFLAGS) -c src/str.c -o obj/str.o

obj/test.o: src/test.c include/test_str.h | obj
	gcc $(CFLAGS) -c src/test.c -o obj/test.o

obj/test_str.o: src/test_str.c include/str.h | obj
	gcc $(CFLAGS) -c src/test_str.c -o obj/test_str.o


clean:
	rm -r obj
	rm lab_02
