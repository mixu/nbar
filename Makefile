build:
	gcc -std=c99 -pedantic -Wall -lX11 ./src/nbar.c -o ./nbar

clean:
	rm ./nbar
