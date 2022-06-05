

prog: graphics.o keys.o movements.o levelLoader.o main.o 
	gcc -Wall -o $@ $^

graphics.o: graphics.c
	gcc -Wall -c $<
keys.o: keys.c
	gcc -Wall -c $<
movements.o: movements.c
	gcc -Wall -c $<
main.o: main.c
	gcc -Wall -c $<

main.o: levelLoader.c
	gcc -Wall -c $<


clean: rm *.o 