solution: main.o particles.o
	gcc -o particles main.o particles.o -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o particles
