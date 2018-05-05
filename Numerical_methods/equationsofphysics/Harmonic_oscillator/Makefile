Target = harmonicRK4 general	
ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)
all: $(Target)

harmonicRK4: harmonicRK4.cpp
	g++ -o $@ harmonicRK4.cpp $(ROOTFLAGS) $(ROOTLIBS)
general: general.cpp
	g++ -o $@ general.cpp $(ROOTFLAGS) $(ROOTLIBS)
clean:	
	rm -f $(Target)
