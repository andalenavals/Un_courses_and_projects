Target = onda onda1 difusion difusion1D difusionCN 
ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)
all: $(Target)
onda: onda.cpp
	g++ -ggdb -o $@ onda.cpp $(ROOTFLAGS) $(ROOTLIBS)
onda1: onda1.cpp
	g++ -ggdb -o $@ onda1.cpp $(ROOTFLAGS) $(ROOTLIBS)
difusion: difusion.cpp
	g++ -ggdb -o $@ difusion.cpp $(ROOTFLAGS) $(ROOTLIBS)
difusion1D: difusion1D.cpp
	g++ -ggdb -o $@ difusion1D.cpp $(ROOTFLAGS) $(ROOTLIBS)
difusionCN: difusionCN.cpp
	g++ -ggdb -o $@ difusionCN.cpp $(ROOTFLAGS) $(ROOTLIBS)
clean:	
	rm -f $(Target)
