
CFLAGS = `sdl2-config --cflags`
LFLAGS = `sdl2-config --libs` -lSDL2_image
SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:src/%.cpp=build/%.o)

all: username

username: build/prog
	cp $< $@


build/prog: $(OBJS)
	g++ $^ $(LFLAGS) -o $@ 

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $< $(CFLAGS) -c -o $@

clean: 
	rm -rf build dependencies.make username

run: username
	./username 

.PHONY: all clean run

dependencies.make:
	g++ -MM src/*.cpp > dependencies.make

-include dependencies.make
