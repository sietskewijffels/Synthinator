
CC = g++

CFLAGS = -lasound -pthread -lncurses

DEPS = oscillator.hpp waveform.hpp
OBJ = oscillator.o waveform.o main.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)
