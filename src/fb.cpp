#include "fb.h"

#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>

PAXFramebuffer::PAXFramebuffer()
{
    framebuffer_fd = open("/dev/fb", O_RDWR);
    if (framebuffer_fd == -1)
    {
        throw "Error: cannot open framebuffer device";
    }
    if (ioctl(framebuffer_fd, FBIOGET_FSCREENINFO, &finfo) == -1)
    {
        throw "Error reading fixed information";
    }
    if (ioctl(framebuffer_fd, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        throw "Error reading variable information";
    }
    std::size_t screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    fb = (uint16_t *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_fd, 0);
    if (fb == (uint16_t *)-1)
    {
        throw "Error: failed to map framebuffer device to memory";
    }
}

PAXFramebuffer::~PAXFramebuffer()
{
    munmap(fb, vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8);
    close(framebuffer_fd);
}