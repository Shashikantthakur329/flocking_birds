CXX = g++
name = main
inputName = $(name).cpp
dep = birds.hpp
objName = $(name).o
raylibPath = /usr/local/lib/libraylib.a

all: $(name) $(dep)

$(name): $(objName) $(raylibPath)
	$(CXX) -g -o $(name) $(objName) $(raylibPath)

$(objName): $(inputName)
	$(CXX) -g -c $(inputName)

clean:
	@rm -f *.o $(name)