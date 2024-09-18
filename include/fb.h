#ifndef FB_H
#define FB_H

#include <cstdint>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>

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
    int fbfd;
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
    PAXFramebuffer()
    {
        fbfd = open("/dev/fb", O_RDWR);
        if (fbfd == -1)
        {
            throw "Error: cannot open framebuffer device";
        }
        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1)
        {
            throw "Error reading fixed information";
        }
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1)
        {
            throw "Error reading variable information";
        }
        std::size_t screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
        fb = (uint16_t*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
        if (fb == (uint16_t*)-1)
        {
            throw "Error: failed to map framebuffer device to memory";
        }
    }

    uint16_t& pixel(int x, int y)
    {
        return fb[getOffset(x, y)];
    }

    void drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
    {
        pixel(x, y) = rgb16(r, g, b);
    }

    ~PAXFramebuffer()
    {
        munmap(fb, vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8);
        close(fbfd);
    }
};

#endif // FB_H