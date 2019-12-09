
CC = g++

CFLAGS = -lasound -pthread -lncurses

DEPS = oscillator.hpp waveform.hpp
OBJ = oscillator.o waveform.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
