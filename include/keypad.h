#ifndef KEYPAD_H
#define KEYPAD_H

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
    // Disable copy constructor and assignment operator
    PAXKeypad(const PAXKeypad &) = delete;
    PAXKeypad &operator=(const PAXKeypad &) = delete;
    // Allow move constructor and assignment operator
    PAXKeypad(PAXKeypad &&) = default;
    PAXKeypad &operator=(PAXKeypad &&) = default;
    
    PAXKeypad();
    ~PAXKeypad();
    int getKey();
};

#endif