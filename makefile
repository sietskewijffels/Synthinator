
CC = g++

CFLAGS = -lasound -pthread

DEPS = Note.hpp AudioThread.hpp EventQueue.hpp InputThread.hpp keyboard.hpp oscillator.hpp waveform.hpp
OBJ = Note.cpp AudioThread.o EventQueue.o InputThread.o keyboard.o oscillator.o waveform.o main.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)
