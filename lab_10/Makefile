CFLAGS = -I include -Wall -Wextra -Werror -std=c++11

lab_10: obj/Circle.o obj/Figure.o obj/main.o obj/Rectangle.o obj/Scheme.o
	g++ $(CFLAGS) obj/Circle.o obj/Figure.o obj/main.o obj/Rectangle.o obj/Scheme.o -o lab_10

obj:
	mkdir obj


obj/main.o: src/main.cpp include/Circle.hpp include/Rectangle.hpp include/Scheme.hpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/Circle.o: src/Circle.cpp include/Circle.hpp | obj
	g++ $(CFLAGS) -c src/Circle.cpp -o obj/Circle.o

obj/Figure.o: src/Figure.cpp include/Figure.hpp | obj
	g++ $(CFLAGS) -c src/Figure.cpp -o obj/Figure.o

obj/Rectangle.o: src/Rectangle.cpp include/Rectangle.hpp | obj
	g++ $(CFLAGS) -c src/Rectangle.cpp -o obj/Rectangle.o

obj/Scheme.o: src/Scheme.cpp include/Scheme.hpp | obj
	g++ $(CFLAGS) -c src/Scheme.cpp -o obj/Scheme.o


clean:
	rm -r obj
	rm lab_10
