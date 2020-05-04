# Synthinator

A command line synthesizer.

# To Do:

* Configurable Keyboard device
* Actual UI
* Add stereo interleaving
* Fix magic numbers
* Implement different waveforms
* Composite notes

# Notes:

> Take care that the correct keyboard device is used (even when name is correct) events might only be obtained when multiple keys are held simultaneously when wrong device is used.

As of right now the keyboard device is hard-coded as a constant in `keyboard.cpp`.
