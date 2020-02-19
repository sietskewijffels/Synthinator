
CC = g++

CFLAGS = -lasound -pthread

DEPS = AudioThread.hpp EventQueue.hpp InputThread.hpp keyboard.hpp oscillator.hpp waveform.hpp
OBJ = AudioThread.o EventQueue.o InputThread.o keyboard.o oscillator.o waveform.o main.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)
