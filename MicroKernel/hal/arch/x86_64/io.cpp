#include <io.hpp>

namespace hal::io {
uint8_t inb(uint16_t port) {
    uint8_t val;
    asm volatile("inb %%dx, %%al"
                 : "=a"(val)
                 : "d"(port));
    return val;
}
void outb(uint16_t port, uint8_t val) {
    asm volatile(
        "outb %%al, %%dx"
        :
        : "d"(port), "a"(val));
}
}  // namespace hal::io
