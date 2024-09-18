#include "touchscreen.h"

#include <cstddef>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

PAXTouchscreen::PAXTouchscreen()
{
    touchpad_fd = open("/dev/tp", O_RDONLY | O_NONBLOCK);
    if (touchpad_fd < 0)
    {
        throw "Failed to open /dev/tp";
    }
}

TouchEvent PAXTouchscreen::getTouchEvent()
{
    int rd;
    struct input_event ev0[64]; 
    rd = read(touchpad_fd, ev0, sizeof(struct input_event) * 64);

    TouchEvent ev = {-1, -1, -1};

    if (rd < (int)sizeof(struct input_event))
        return ev;
    
    for (int i = 0; i < rd / (int)sizeof(struct input_event); i++)
    {
        // Screen is inverted, so we need to swap x and y
        if (ev0[i].type == 3 && ev0[i].code == ABS_X)
        {
            ev.y = ev0[i].value;
        }
        else if (ev0[i].type == 3 && ev0[i].code == ABS_Y)
        {
            ev.x = ev0[i].value;
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