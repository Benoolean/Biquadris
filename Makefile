CC = g++
CFLAGS = -std=c++14
objects = square.o block.o grid.o blockgrid.o effect.o blind.o heavy.o level.o biquadris.o main.o

vpath %.h ./headers
vpath %.cc ./src
vpath %.o ./libs

biquadris: $(objects)
	$(CC) $(CFLAGS) $(objects) -o biquadris -lX11

$(objects): %.o: %.cc
	$(CC) $(CFLAGS) -I ./headers -c $< -o ./libs/$@

.PHONY: clean
clean:
	-rm biquadris ./libs/*.o
