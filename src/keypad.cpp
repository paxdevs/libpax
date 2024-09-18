#include "keypad.h"

#include <cstddef>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

PAXKeypad::PAXKeypad()
{
    keypad_fd = open("/dev/keypad", O_RDONLY | O_NONBLOCK);
    if (keypad_fd < 0)
    {
        throw "Failed to open /dev/keypad";
    }
}
int PAXKeypad::getKey()
{
    struct input_event ev0;
    std::size_t rd;
    rd = ::read(keypad_fd, &ev0, sizeof(struct input_event));
    if (rd < sizeof(struct input_event))
        return 0;

    if (ev0.type != 1)
    {
        // some paxes return first event with weird value ... discard this one
        if (ev0.value != 0 && ev0.value != 1)
        {
            return -1;
        }
    }

    if (ev0.value == 1)
    {
        return ev0.code;
    }
    else
    {
        return 0;
    }
}
PAXKeypad::~PAXKeypad()
{
    close(keypad_fd);
}