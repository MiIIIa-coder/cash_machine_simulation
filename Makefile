OBJECTS = src/main.o src/simulation.o src/people.o src/cash_machine.o
HEADERS = hdr/simulation.hpp hdr/people.hpp hdr/cash_machine.hpp
CC = g++
CFLAGS = -Wall -fopenmp

.PHONY: all

all: cash_machine

cash_machine: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o cash_machine

src/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run clean

run: all
	./cash_machine

clean: 
	rm $(OBJECTS)

