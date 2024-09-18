#include "touchscreen.h"

#include <cstddef>
#include <fcntl.h>
#include <linux/input.h>
#include <optional>
#include <unistd.h>

PAXTouchscreen::PAXTouchscreen()
{
    touchpad_fd = open("/dev/keypad", O_RDONLY | O_NONBLOCK);
    if (touchpad_fd < 0)
    {
        throw "Failed to open /dev/keypad";
    }
}

std::optional<TouchEvent> PAXTouchscreen::getTouchEvent()
{
    int rd;
    struct input_event ev0[64]; 
    rd = read(touchpad_fd, ev0, sizeof(struct input_event) * 64);

    if (rd < sizeof(struct input_event))
        return std::nullopt;
    
    TouchEvent ev;
    for (int i = 0; i < rd / sizeof(struct input_event); i++)
    {
        if (ev0[i].type == 3 && ev0[i].code == ABS_X)
        {
            ev.x = ev0[i].value;
        }
        else if (ev0[i].type == 3 && ev0[i].code == ABS_Y)
        {
            ev.y = ev0[i].value;
        }

        if (ev0[i].type == 1 && ev0[i].code == 330)
        {
            if (ev0[i].value == 1)
            {
                ev.pressed = 1;
            }
            else
            {
                ev.pressed = 0;
            }
        }
    }
    return ev;
}

PAXTouchscreen::~PAXTouchscreen()
{
    close(touchpad_fd);
}