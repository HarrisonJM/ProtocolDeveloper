CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp helloWorld.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=helloWorld.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: $(OBJECTS)
	rm *.o
	rm *.out