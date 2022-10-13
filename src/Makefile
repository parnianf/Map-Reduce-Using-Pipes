all : mapProcess reduceProcess MapReduced.out


mapProcess : mapProcessMain.o mapProcess.o
	g++ mapProcessMain.o mapProcess.o -o mapProcess
	
mapProcessMain.o : mapProcessMain.cpp mapProcess.cpp mapProcess.h
	g++ -c mapProcessMain.cpp -o mapProcessMain.o

mapProcess.o :  mapProcess.cpp mapProcess.h
	g++ -c mapProcess.cpp -o mapProcess.o

reduceProcess : reduceProcessMain.o reduceProcess.o
	g++ reduceProcessMain.o reduceProcess.o -o reduceProcess

build/reduceProcessMain.o : reduceProcessMain.cpp reduceProcess.cpp reduceProcess.h
	g++ -c reduceProcessMain.cpp -o reduceProcessMain.o 

build/reduceProcess.o : reduceProcess.cpp reduceProcess.h
	g++ -c reduceProcess.cpp -o reduceProcess.o

MapReduced.out :  wordCounterMain.o wordCounter.o

	g++ wordCounterMain.o wordCounter.o -o  MapReduced.out

wordCounterMain.o : wordCounterMain.cpp wordCounter.h wordCounter.cpp
	g++ -c wordCounterMain.cpp -o wordCounterMain.o

wordCounter.o : wordCounter.cpp wordCounter.h
	g++ -c wordCounter.cpp -o wordCounter.o