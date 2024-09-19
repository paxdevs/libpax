#include "pax/printer.h"

#include <fcntl.h>
#include <linux/input.h>
#include <linux/soundcard.h>
#include <unistd.h>

PAXPrinter::PAXPrinter()
{
    printer_fd = open("/dev/printer", O_WRONLY);
}

int PAXPrinter::print(const void *buf, int len)
{
    return write(printer_fd, buf, len);
}

int PAXPrinter::print(PAXPrinterCanvas &canvas)
{
    auto& buf = canvas.getPrintBuffer();
    return print(buf.data(), buf.size());
}