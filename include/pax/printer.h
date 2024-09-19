#ifndef PRINTER_H
#define PRINTERD_H

class PAXPrinter
{
private:
    int printer_fd;

public:
    // Disable copy constructor and assignment operator
    PAXPrinter(const PAXPrinter &) = delete;
    PAXPrinter &operator=(const PAXPrinter &) = delete;
    // Allow move constructor and assignment operator
    PAXPrinter(PAXPrinter &&) = default;
    PAXPrinter &operator=(PAXPrinter &&) = default;

    PAXPrinter();
    ~PAXPrinter();
    int print(const void *buf, int len);
};

#endif