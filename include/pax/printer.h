#ifndef PRINTER_H
#define PRINTERD_H

#include <cstdint>
#include <vector>

#define PAX_PRINTER_WIDTH 384

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
    int print(PAXPrinterCanvas &canvas);
};

class PAXPrinterCanvas
{
private:
    std::vector<uint8_t> buffer;

public:
    PAXPrinterCanvas(std::size_t height) : buffer((PAX_PRINTER_WIDTH / 8) * height, 0) {}
    ~PAXPrinterCanvas() = default;

    inline void setPixel(int x, int y, bool value)
    {
        auto &pix = buffer[y * (PAX_PRINTER_WIDTH / 8) + (x / 8)];
        int offset = 7 - (x % 8);
        if (value)
        {
            pix |= (1 << offset);
        }
        else
        {
            pix &= ~(1 << offset);
        }
    }

    inline bool getPixel(int x, int y) const
    {
        auto pix = buffer[y * (PAX_PRINTER_WIDTH / 8) + (x / 8)];
        int offset = 7 - (x % 8);
        return (pix >> offset) & 1;
    }

    inline std::vector<uint8_t> &getBuffer()
    {
        return buffer;
    }
};

#endif