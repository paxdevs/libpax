#ifndef FB_H
#define FB_H

#include <cstdint>
#include <linux/fb.h>

// Maximum x
#define PAX_FRAMEBUFFER_WIDTH 240
// Maximum y
#define PAX_FRAMEBUFFER_HEIGHT 320

inline uint16_t rgb16(uint8_t r, uint8_t g, uint8_t b)
{
    return (r << 11) | (g << 5) | b;
}

class PAXFramebuffer
{
private:
    // Framebuffer file descriptor
    int framebuffer_fd;

    // Framebuffer attributes
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    // Framebuffer pixels
    uint16_t *fb;

    inline uint32_t getOffset(int x, int y)
    {
        // Screen is rotated
        return (y + vinfo.xoffset) +
               (x + vinfo.yoffset) * (finfo.line_length / 2);
    }

public:
    // Disable copy constructor and assignment operator
    PAXFramebuffer(const PAXFramebuffer &) = delete;
    PAXFramebuffer &operator=(const PAXFramebuffer &) = delete;
    // Allow move constructor and assignment operator
    PAXFramebuffer(PAXFramebuffer &&) = default;
    PAXFramebuffer &operator=(PAXFramebuffer &&) = default;

    PAXFramebuffer();
    ~PAXFramebuffer();
    inline uint16_t& pixel(int x, int y)
    {
        return fb[getOffset(x, y)];
    }
    inline void drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
    {
        pixel(x, y) = rgb16(r, g, b);
    }
};

#endif // FB_H