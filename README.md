# Synthinator

A command line synthesizer. Met coowle shizz enzo jwz.

# Note Lifecycle

1. Key is pressed:
    * `read()` in `Keyboard::keyboardLoop()` unblocks and reads key pressed
    * Gets the frequency corresponding to that key and sets the type to `NOTE_ON`
2. Event gets added to `EventQueue` by the `Keyboard::keyboardLoop`
3. On next buffer frame `AudioThread::onPlayback()` creates a new `Note` and adds it to the `playing` vector
    * `Note`'s constructor creates `Oscillator` objects
    * `Note`'s constructor sets up the `base_envelope` filter.
4. Once events are handled `AudioThread::onPlayback` calls `Note::synthesize()` on all notes in `playing`
    * calls `Oscillator::oscillate` on all oscillators
    * calls `Filter::doFilterings` on the obtained buffer
    * Lastly runs the base envelope filter for that note
5. Repeat last step untill Key is released
6. Does step 1 and 2 for a `NOTE_OFF` event
7. On the next buffer frame `AudioThread::onPlayback` finds the notes in `playing` that have `analog_freq` same as the event. and calls `Note::signalOff`.
    * Sets the envelope phase to release.
8. Again repeat step 4 until envelope release phase is finished which sets envelope state to `FINISHED`.
    * on the next call to `Note::synthesize`, `note_active` gets set to false
9. In `AudioThread::onPlayback`, `note_active` is checked and the note is removed from the `playing` vector.


# Notes:

## Keyboard device
> Take care that the correct keyboard device is used (even when name is correct) events might only be obtained when multiple keys are held simultaneously when wrong device is used.

As of right now the keyboard device is hard-coded as a constant in `keyboard.cpp`.

## Root privileges

Because the keyboard is read directly from the device, the keyboard class needs root priviles to run..
