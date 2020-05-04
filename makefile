
CC = g++

CFLAGS = -Wall -Wextra -lasound -pthread

DEPS = Filter.hpp EnvelopeFilter.hpp Note.hpp AudioThread.hpp EventQueue.hpp InputThread.hpp keyboard.hpp oscillator.hpp waveform.hpp
OBJ = Filter.o EnvelopeFilter.o Note.o AudioThread.o EventQueue.o InputThread.o keyboard.o oscillator.o waveform.o main.o


./bin/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o
