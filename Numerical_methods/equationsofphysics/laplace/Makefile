Target = laplace	
ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)
all: $(Target)
laplace: laplace.cpp
	g++ -o $@ laplace.cpp $(ROOTFLAGS) $(ROOTLIBS)

clean:	
	rm -f $(Target)
