Target = ajuste resta espectro calibracion canalenergia
ROOTFLAGS = $(shell root-config --cflags)
#ROOTLIBS = $(shell root-config --libs)$

ROOTLIBS  = -L/usr/lib/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lSpectrum -lRooFit -lRooFitCore


all: $(Target)
ajuste: ajuste.cpp
	g++ -ggdb -o $@ ajuste.cpp $(ROOTFLAGS) $(ROOTLIBS)
resta: resta.cpp
	g++ -ggdb -o $@ resta.cpp $(ROOTFLAGS) $(ROOTLIBS)
espectro: espectro.cpp
	g++ -ggdb -o $@ espectro.cpp $(ROOTFLAGS) $(ROOTLIBS)
calibracion: calibracion.cpp
	g++ -ggdb -o $@ calibracion.cpp $(ROOTFLAGS) $(ROOTLIBS)
canalenergia: canalenergia.cpp
	g++ -ggdb -o $@ canalenergia.cpp $(ROOTFLAGS) $(ROOTLIBS)
clean: 
	rm -f $(Target)
