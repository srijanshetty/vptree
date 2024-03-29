CC=g++ -std=c++11
CFLAGS=-Wall -c
DEBUG=-g

.PHONY: all build restore setup-files clean-all clean-files

# Build the tree
driver.o: driver.cpp vptree.o point.o
	$(CC) $(DEBUG) driver.cpp vptree.o point.o -o tree.out

# Build the vptree library
vptree.o: point.h vptree.h vptree.cpp config.h statistics.o
	$(CC) $(CFLAGS) $(DEBUG) vptree.cpp

# Build the point library
point.o: point.h point.cpp config.h
	$(CC) $(CFLAGS) $(DEBUG) point.cpp

# Build the statistics library
statistics.o: statistics.cpp
	$(CC) $(CFLAGS) $(DEBUG) statistics.cpp

clean:
	rm -f *.o *.out *.gch
