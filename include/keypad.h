#ifndef KEYPAD_H
#define KEYPAD_H

#include <fcntl.h>
#include <linux/input.h>
#include <stddef.h>
#include <unistd.h>

/* Return codes:
  2 - key 1
  3 - key 2
  4 - key 3
  5 - key 4
  6 - key 5
  7 - key 6
  8 - key 7
  9 - key 8
 10 - key 9
 11 - key 0
 69 - Alpha
102 - Func
 14 - Back (YELLOW)
 28 - Enter (GREEN)
223 - ESC (red)
*/

class PAXKeypad
{
private:
    int keypad_fd;

public:
    PAXKeypad()
    {
        keypad_fd = open("/dev/keypad", O_RDONLY | O_NONBLOCK);
        if (keypad_fd < 0)
        {
            throw "Failed to open /dev/keypad";
        }
    }
    int read()
    {
        struct input_event ev0;
        size_t rd;
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
    ~PAXKeypad()
    {
        close(keypad_fd);
    }
};

#endif