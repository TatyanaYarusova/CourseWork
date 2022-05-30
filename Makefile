all: main.o demon.o rectangle.o reflection.o help.o info.o collage.o
	gcc main.o demon.o rectangle.o reflection.o help.o info.o collage.o -o cw -lm

main.o: main.c
	gcc -c main.c

demon.o: demon.c
	gcc -c demon.c

rectangle.o: rectangle.c
	gcc -c rectangle.c

reflection.o: reflection.c
	gcc -c reflection.c

help.o: help.c
	gcc -c help.c

collage.o: collage.c
	gcc -c collage.c

info.o: info.c
	gcc -c info.c

clean:
	rm *.o