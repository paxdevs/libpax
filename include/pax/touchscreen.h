#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

struct TouchEvent {
    int x;
    int y;
    int pressed;
};

class PAXTouchscreen
{
private:
    int touchpad_fd;

public:
    // Disable copy constructor and assignment operator
    PAXTouchscreen(const PAXTouchscreen &) = delete;
    PAXTouchscreen &operator=(const PAXTouchscreen &) = delete;
    // Allow move constructor and assignment operator
    PAXTouchscreen(PAXTouchscreen &&) = default;
    PAXTouchscreen &operator=(PAXTouchscreen &&) = default;
    
    PAXTouchscreen();
    ~PAXTouchscreen();
    TouchEvent getTouchEvent();
};

#endif