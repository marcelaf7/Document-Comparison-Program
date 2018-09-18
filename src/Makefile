OBJS = main.o Exceptions.o Document.o ReadLvl.o Porter.o DocSim.o
CF = -g -I. -Wall -c
EXE = Document-Comparison
TARSOURCE = DocSim.cpp DocSim.h Document.cpp Document.h Exceptions.cpp Exceptions.h main.cpp Makefile Porter.cpp Porter.h ReadLvl.cpp ReadLvl.h
TARFILE = Document-Comparison.tar

Document-Comparison: $(OBJS)
	g++ $(OBJS) -Wall -o $(EXE)

main.o: main.cpp Exceptions.h Document.h DocSim.h
	g++ main.cpp $(CF)
	
Exceptions.o: Exceptions.cpp Exceptions.h
	g++ Exceptions.cpp $(CF)
	
Document.o: Document.cpp Document.h Exceptions.h ReadLvl.h Porter.h
	g++ Document.cpp $(CF)
	
ReadLvl.o: ReadLvl.cpp ReadLvl.h
	g++ ReadLvl.cpp $(CF)
	
Porter.o: Porter.cpp Porter.h
	g++ Porter.cpp $(CF)
	
DocSim.o: DocSim.cpp DocSim.h Document.h
	g++ DocSim.cpp $(CF)
	
clean:
	-rm $(EXE) $(OBJS)

tar:
	tar -cvf $(TARFILE) main.cpp Makefile $(TARSOURCE)
