all: mean-plugin plugin-test zeroes-plugin

mean-plugin: mean-plugin.o
	gcc -shared -g -o mean-plugin.so mean-plugin.o -lm

mean-plugin.o: mean-plugin.c
	gcc -c -g -fpic mean-plugin.c

zeroes-plugin: zeroes-plugin.o
	gcc -shared -g -o zeroes-plugin.so zeroes-plugin.o -lm

zeroes-plugin.o: zeroes-plugin.c
	gcc -c -g -fpic zeroes-plugin.c

plugin-test: plugin-test.o
	gcc -shared -g -o plugin-test.so plugin-test.o

plugin-test.o:
	gcc -c -g -fpic plugin-test.c

clean:
	rm *.o
	rm *.so
