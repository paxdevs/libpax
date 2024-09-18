#ifndef SOUND_H
#define SOUND_H

class PAXSound
{
private:
    int dsp_fd;

public:
    // Disable copy constructor and assignment operator
    PAXSound(const PAXSound &) = delete;
    PAXSound &operator=(const PAXSound &) = delete;
    // Allow move constructor and assignment operator
    PAXSound(PAXSound &&) = default;
    PAXSound &operator=(PAXSound &&) = default;

    PAXSound();
    ~PAXSound();
    int setSamplerate(int rate);
    int setSamplesize(int bits);
    int setChannels(int channels);
    int playSound(const void *buf, int len);
};

#endif