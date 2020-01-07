
CC = g++

CFLAGS = -lasound -pthread -lncurses

DEPS = keyboard.hpp oscillator.hpp waveform.hpp 
OBJ = keyboard.o oscillator.o waveform.o main.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)
