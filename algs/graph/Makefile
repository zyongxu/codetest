CC=g++
CFLAGS=-c
TAR=testgraph
SRC1=graph
SRC2=tree

$(TAR): $(TAR).o $(SRC1).o
	$(CC) -o testgraph $(TAR).o $(SRC1).o

$(TAR).o: $(TAR).cpp $(SRC1).h $(SRC2).h
	$(CC) $(CFLAGS) $(TAR).cpp

$(SRC1).o: $(SRC1).cpp $(SRC1).h $(SRC2).h
	$(CC) $(CFLAGS) $(SRC1).cpp

clean:
	rm -f *.o $(TAR)
