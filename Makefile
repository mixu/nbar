build:
	gcc -std=c99 -pedantic -Wall -lX11 nwmbar.c -o ./nwmbar

clean:
	rm ./nwmbar
