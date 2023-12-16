solution: main.o bellmanford.o
	gcc -o bellmanford main.o bellmanford.o -lm -fopenmp -O3

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o bellmanford
