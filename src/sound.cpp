#include "pax/sound.h"

#include <fcntl.h>
#include <linux/input.h>
#include <linux/soundcard.h>
#include <unistd.h>

PAXSound::PAXSound()
{
    dsp_fd = open("/dev/snd/dsp", O_WRONLY | O_NONBLOCK);

    setSamplerate(48000);
    setSamplesize(16);
    setChannels(1);
}

int PAXSound::setSamplerate(int rate)
{
    return ioctl(dsp_fd, SOUND_PCM_WRITE_RATE, &rate);
}

int PAXSound::setSamplesize(int bits)
{
    return ioctl(dsp_fd, SOUND_PCM_WRITE_BITS, &bits);
}

int PAXSound::setChannels(int channels)
{
    return ioctl(dsp_fd, SOUND_PCM_WRITE_CHANNELS, &channels);
}

int PAXSound::playSound(const void *buf, int len)
{
    return write(dsp_fd, buf, len);
}