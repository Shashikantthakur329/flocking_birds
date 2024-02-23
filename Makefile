CXX = g++
name = main
gprof = gmon.out
gprofOut = analysis.txt
inputName = $(name).cpp
dep = birds.hpp
objName = $(name).o
raylibPath = /usr/local/lib/libraylib.a

all: $(name) $(dep)

$(name): $(objName) $(raylibPath)
	$(CXX) -pg -o $(name) $(objName) $(raylibPath)

$(objName): $(inputName)
	$(CXX) -pg -c $(inputName)

$(gprofOut): $(gprof)
	gprof $(name) $(gprof) > $(gprofOut)
	
clean:
	@rm -f *.o $(name)