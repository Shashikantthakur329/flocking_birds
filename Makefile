CXX = g++
name = main
inputName = $(name).cpp
objName = $(name).o
raylibPath = /usr/local/lib/libraylib.a

all: $(name)

$(name): $(objName) $(raylibPath)
	$(CXX) -o $(name) $(objName) $(raylibPath)

$(objName): $(inputName)
	$(CXX) -c $(inputName)

clean:
	@rm -f *.o $(name)