
# Pop when releasing note

There is a pop when alternating between notes. E.g. when the first note is released while the second note is still playing. Only occurs when the first note is released.

# Weird double free

Caused by `FrameBuffer::operator*()`. On return, the copy of `*this` gets destroyed and thus frees the buffer. (I think...)

## Fix:

Copy constructor now explicitly `memcpy()`'s the buffer.

# Weird segfault

* Seems to be caused by `delete waveform;` in `Oscillator::~Oscillator`;
* Because new oscillators are created on the stack.
    * So the destrucors are called right after `Oscillator`'s constructor finishes resulting in a use-after-free.
* Same happens for `Note` but is less apparent
* New FrameBuffer in the heap has the same problem

Fix would be to allocate all `Note`s and `Oscillators` that are placed in a vector on the heap. The respective destructors then need to free the elements of these vectors.

# Let buffers live on the heap

* Buffers are more than 1 KB..
