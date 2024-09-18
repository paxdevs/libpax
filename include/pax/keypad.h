#ifndef KEYPAD_H
#define KEYPAD_H

enum KeyCode
{
    INVALID = -1,
    NONE = 0,
    KEY_1 = 2,
    KEY_2 = 3,
    KEY_3 = 4,
    KEY_4 = 5,
    KEY_5 = 6,
    KEY_6 = 7,
    KEY_7 = 8,
    KEY_8 = 9,
    KEY_9 = 10,
    KEY_0 = 11,
    KEY_ALPHA = 69,
    KEY_FUNC = 102,
    KEY_BACK = 14,
    KEY_ENTER = 28,
    KEY_ESC = 223
};

class PAXKeypad
{
private:
    int keypad_fd;

public:
    // Disable copy constructor and assignment operator
    PAXKeypad(const PAXKeypad &) = delete;
    PAXKeypad &operator=(const PAXKeypad &) = delete;
    // Allow move constructor and assignment operator
    PAXKeypad(PAXKeypad &&) = default;
    PAXKeypad &operator=(PAXKeypad &&) = default;

    PAXKeypad();
    ~PAXKeypad();
    KeyCode getKey();
};

#endif