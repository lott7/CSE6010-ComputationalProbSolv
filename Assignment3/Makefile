solution: main.o all.o
	gcc -o connected main.o all.o -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o connected
