#include <iostream>
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <thread>
#include <stdlib.h>
#include <string>

#include "oscillator.hpp"
#include "InputThread.hpp"
#include "keyboard.hpp"

#define BUF_SIZE 512
#define SAMPLE_FREQ 48000

float buffer[BUF_SIZE];
float freq = 440;
unsigned char gain  = 0x10;

Oscillator osc = Oscillator(freq, SAMPLE_FREQ, WaveType::WAVE_SINE);


int onPlayback(snd_pcm_t *pcm_handle, snd_pcm_sframes_t nframes){

    osc.oscillate();

    return snd_pcm_writei(pcm_handle, buffer, nframes);
}


void make_sound(snd_pcm_t *pcm_handle){

    std::cerr << "Soundshizz" << std::endl;

    //Setup pollstuff
    int nfds = snd_pcm_poll_descriptors_count(pcm_handle);
    struct pollfd *pfds = (struct pollfd*) alloca(sizeof(struct pollfd) * nfds);

    snd_pcm_poll_descriptors(pcm_handle, pfds, nfds);

    osc.buffer = buffer;

    std::cerr << "Buffer size: " << sizeof(buffer) / sizeof(float) << std::endl;

    while(1){

        if (freq == 0)
            break;

        if (poll(pfds, nfds, 1000) > 0){
            if (pfds->revents > 0){
                if (onPlayback(pcm_handle, BUF_SIZE) < BUF_SIZE){
                    // Buffer underrun, restart
                    fprintf(stderr, "Underrun!\n");
                    snd_pcm_prepare(pcm_handle);
                }
            }
        }
    }

    snd_pcm_close(pcm_handle);


}


void setFreq(char in){

    //TODO: make notes  custom
    switch(in){
    case 'z': // C
        freq = 261.63;
        break;
    case 's': // C#
        freq = 277.18;
        break;
    case 'x': // D
        freq = 293.66;
        break;
    case 'd': // D#
        freq = 311.13;
        break;
    case 'c': // E
        freq = 329.63;
        break;
    case 'v': // F
        freq = 349.23;
        break;
    case 'g': // F#
        freq = 369.99;
        break;
    case 'b': // G
        freq = 392.00;
        break;
    case 'h': // G#
        freq = 415.30;
        break;
    case 'n': // A
        freq = 440.00;
        break;
    case 'j': // A#
        freq = 466.16;
        break;
    case 'm': // B
        freq = 493.88;
        break;
    case ',': // C
        freq = 523.25;
        break;
    case 'q':
        freq = 0;
        break;
    }

}



int main (int argc, char *argv[]){

    std::cerr << "Yo Whaddup!" << std::endl; // TODO: make log file instead of stderr

    snd_pcm_t *pcm_handle;
    snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
    //snd_pcm_hw_params_t *hwparams;

    if (snd_pcm_open(&pcm_handle, "default", stream, 0) < 0){

        fprintf(stderr, "Error opening sound device Yo!");
        return -1;

    }


    if (snd_pcm_set_params(pcm_handle,
                SND_PCM_FORMAT_FLOAT_LE,
                SND_PCM_ACCESS_RW_INTERLEAVED,
                1,
                SAMPLE_FREQ,
                0,
                10000) < 0){

        fprintf(stderr, "Playback open error!");
        return -1;
    }


    std::thread audio_thread;

    audio_thread = std::thread(make_sound, pcm_handle);
    InputThread input_thread;

    audio_thread.join();


    return 0;
}
