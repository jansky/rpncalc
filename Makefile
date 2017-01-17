all: rpncalc plugins

rpncalc: calc.o stack.o main.o trig.o math.o stat.o var.o eval.o plugin.o
	cc -g -o rpncalc calc.o stack.o main.o trig.o math.o stat.o var.o eval.o plugin.o -lm -ldl

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

eval.o: eval.c
	cc -g -c eval.c

plugin.o: plugin.c
	cc -g -c plugin.c

.PHONY: clean plugins
clean:
	rm rpncalc
	rm *.o
	$(MAKE) -C plugins clean

install:
	cp rpncalc /usr/bin

deinstall:
	rm /usr/bin/rpncalc

plugins:
	$(MAKE) -C plugins
