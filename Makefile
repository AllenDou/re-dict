CC=gcc
CFLAGS= -Wall -g -ggdb -rdynamic
OBJ= main.o dict.o sds.o zmalloc.o
BIN=bin
TEST=test

all:$(TEST)
$(TEST):$(OBJ)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^	
clean:
	rm -rf $(BIN)/* *.o
