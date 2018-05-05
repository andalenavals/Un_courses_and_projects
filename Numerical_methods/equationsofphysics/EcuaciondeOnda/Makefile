Target = onda1Deuler onda onda1DCN
ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)
all: $(Target)
onda1Deuler: onda1Deuler.cpp
	g++ -o $@ onda1Deuler.cpp $(ROOTFLAGS) $(ROOTLIBS)
onda1DCN: onda1DCN.cpp
	g++ -o $@ onda1DCN.cpp $(ROOTFLAGS) $(ROOTLIBS)
onda: onda.cpp
	g++ -o $@ onda.cpp $(ROOTFLAGS) $(ROOTLIBS)

clean:	
	rm -f $(Target)
