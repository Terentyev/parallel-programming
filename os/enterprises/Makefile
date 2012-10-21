#CC=g++
CC=clang
#CFLAGS=-I./inc -O3 -pthread
CFLAGS=-I./inc -ggdb -g3 -O0 -DDEBUG -pthread
LDFLAGS=-pg -pthread
LD=g++
SOURCES=main.cpp callbacks.cpp consts.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BIN=enterprises

all: $(BIN) $(SOURCES)

$(BIN): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f -- *.o $(BIN) gmon.out > /dev/null
