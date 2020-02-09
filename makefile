
CC = g++

CFLAGS = -lasound -pthread 

DEPS = InputThread.hpp keyboard.hpp oscillator.hpp waveform.hpp
OBJ = InputThread.o keyboard.o oscillator.o waveform.o main.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)
