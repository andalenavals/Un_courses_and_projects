Target = gas nucleos termico
ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)
all: $(Target)
gas: gas.cpp
	g++  -ggdb -o  $@ gas.cpp $(ROOTFLAGS) $(ROOTLIBS)
nucleos: nucleos.cpp
	g++  -ggdb -o  $@ nucleos.cpp $(ROOTFLAGS) $(ROOTLIBS)
termico: termico.cpp
	g++  -ggdb -o  $@ termico.cpp $(ROOTFLAGS) $(ROOTLIBS)

clean:	
	rm -f $(Target)
