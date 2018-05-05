Target = derivada integral 
ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)
all: $(Target)
derivada: derivada.cpp
	g++ -o $@ derivada.cpp $(ROOTFLAGS) $(ROOTLIBS)
integral: integral.cpp
	g++ -o $@ integral.cpp $(ROOTFLAGS) $(ROOTLIBS)
clean:	
	rm -f $(Target)
