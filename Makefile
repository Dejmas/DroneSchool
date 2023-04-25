# compilation flags
CFLAGS = `sdl2-config --cflags`

# linking flags
LFLAGS = `sdl2-config --libs` -lSDL2_image

# Source Files
SRC = $(wildcard src/*.cpp)

# Object Files
OBJS = $(SRC:src/%.cpp=build/%.o)

# Tests 
TESTS = $(wildcard tests/*.test.cpp)

all: username

username: build/prog $(OBJS)
	cp $< $@


build/prog: $(OBJS)
	g++ $^ $(LFLAGS) -o $@ 

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $< $(CFLAGS) -c -o $@

clean: 
	rm -rf build username dependencies.make debug dependencies.test.make 

run: username
	./username

debug/%.test: tests/%.test.cpp $(filter-out build/main.o,$(OBJS))
	mkdir -p $(@D)
	g++ $(CFLAGS) $(LFLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -I src/ -o $@

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST  && echo $${TEST} ok || echo $${TEST} failed!; done


.PHONY: all clean run

dependencies.make:
	g++ -MM $(CFLAGS) src/*.cpp | sed 's/^\([a-zA-Z][^.]*.o\)/build\/\1/g' > $@

-include dependencies.make

dependencies.test.make:
	g++ -MM $(CFLAGS) -I src tests/*.cpp | sed 's/^\([a-zA-Z][^.]*.o\)/debug\/\1/g' > $@

debug/vector2d.test.o: tests/vector2d.test.cpp src/utils.h

