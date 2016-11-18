all: rpncalc

rpncalc: calc.o stack.o main.o trig.o math.o stat.o var.o
	cc -g -o rpncalc calc.o stack.o main.o trig.o math.o stat.o var.o -lm

calc.o: calc.c
	cc -g -c calc.c

stack.o: stack.c
	cc -g -c stack.c

main.o: main.c
	cc -g -c main.c

trig.o: trig.c
	cc -g -c trig.c

math.o: math.c
	cc -g -c math.c

stat.o: stat.c
	cc -g -c stat.c

var.o: var.c
	cc -g -c var.c

clean:
	rm rpncalc
	rm *.o

install:
	cp rpncalc /usr/bin

deinstall:
	rm /usr/bin/rpncalc
