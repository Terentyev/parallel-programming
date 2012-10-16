#CC=g++
CC=clang
CFLAGS=-I./inc -O3
CFLAGS=-I./inc -ggdb -g3 -O0 -DDEBUG -pg -pthread
#LDFLAGS=-pg
LDFLAGS=-pthread
LD=g++
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BIN=numbers

all: $(BIN) $(SOURCES)

$(BIN): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o $(BIN)
