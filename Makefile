CC = g++
CFLAGS = -std=c++14 -Wall -MMD
objects = square.o block.o grid.o blockgrid.o effect.o blind.o heavy.o level.o biquadris.o window.o main.o
objectPaths := $(objects:%.o=./libs/%.o)
depends := $(objects:%.o=%.d);

-include $(depends)

vpath %.h ./headers
vpath %.cc ./src
vpath %.o ./libs

biquadris: $(objects)
	$(CC) $(CFLAGS) $(objectPaths) -o biquadris -lX11

$(objects): %.o: %.cc
	$(CC) $(CFLAGS) -I ./headers -c $< -o ./libs/$@

.PHONY: clean
clean:
	-rm biquadris ./libs/*.o
