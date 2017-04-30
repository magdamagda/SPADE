OUTPUT = main
COMPILER = g++
FLAGS = -g -std=c++11
OBJ = main.o closedseqrep.o datasetreader.o filehelper.o generatorsrepnegativeborder.o idlist.o representation.o sequence.o spade.o transaction.o 

%.o: %.cpp
	$(COMPILER) -c -o $@ $< $(FLAGS)

all:
	make $(OBJ)
	$(COMPILER) *.o -o$(OUTPUT) $(FLAGS)

clean:
	rm -f $(OBJ) $(OUTPUT)
