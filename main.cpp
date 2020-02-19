#include <iostream>
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <thread>
#include <stdlib.h>
#include <string>
#include <array>

#include "oscillator.hpp"
#include "InputThread.hpp"
#include "keyboard.hpp"
#include "EventQueue.hpp"

#define BUF_SIZE 512
#define SAMPLE_FREQ 48000

float buffer[BUF_SIZE];

unsigned char gain  = 0x10;
float freq = 0;
EventQueue event_queue;

std::vector<Oscillator> playing;

int onPlayback(snd_pcm_t *pcm_handle, snd_pcm_sframes_t nframes){

    // This should probably happen in a separate thread..

    while (!event_queue.queue.empty()){

            // check what event it was

            if (event_queue.queue.front().type == NOTE_OFF && event_queue.queue.front().freq != 0){

                // NOTE_OFF so remove from vector of playing notes
                for (std::vector<Oscillator>::iterator it = playing.begin(); it != playing.end(); it++){

                    if (it->getAnalogFreq() == event_queue.queue.front().freq){

                        std::cerr << "NOTE OFF " << it->getAnalogFreq() << std::endl;
                        playing.erase(it);
                        break;

                    }
                }

            } else if (event_queue.queue.front().type == NOTE_ON && event_queue.queue.front().freq != 0) {
                // NOTE_ON create new oscillator and add to playing notes
                Oscillator osci(event_queue.queue.front().freq, SAMPLE_FREQ, WaveType::WAVE_SINE);
                playing.push_back(osci);
                std::cerr << "NOTE ON " << event_queue.queue.front().freq << std::endl;
            }

            event_queue.queue_mutex.lock();
            event_queue.queue.pop();
            event_queue.queue_mutex.unlock();


    }

    // Reset buffer
    for (int n = 0; n < BUF_SIZE; n++){
        buffer[n] = 0;
    }

    if (!playing.empty()){
    // oscillate all running oscillators
        for (auto note: playing){
            note.oscillate();

            // Print currently playing freqs
            std::cerr << note.getAnalogFreq() << "\t";

            // Add obtained waveform to total buffer
            for (int n = 0; n < BUF_SIZE; n++){
                buffer[n] += note.buffer[n] / playing.size();
            }
        }
    std::cerr << std::endl;
    }



    return snd_pcm_writei(pcm_handle, buffer, nframes);
}


void make_sound(snd_pcm_t *pcm_handle){

    std::cerr << "Soundshizz" << std::endl;

    //Setup pollstuff
    int nfds = snd_pcm_poll_descriptors_count(pcm_handle);
    struct pollfd *pfds = (struct pollfd*) alloca(sizeof(struct pollfd) * nfds);

    snd_pcm_poll_descriptors(pcm_handle, pfds, nfds);

    //osc.buffer = buffer;

    std::cerr << "Buffer size: " << BUF_SIZE << std::endl;

    while(1){

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

    InputThread input_thread(&event_queue);

    audio_thread.join();


    return 0;
}
