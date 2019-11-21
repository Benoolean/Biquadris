objects = square.o block.o grid.o blockgrid.o effect.o blind.o heavy.o level.o biquadris.o main.o

biquadris: $(objects)
	g++ -std=c++14 $(objects) -o biquadris -lX11

.PHONY: clean
clean:
	-rm biquadris $(objects)
