#include "log.hpp"

#include <cstdarg>
#include <cstddef>

#include "ports.hpp"

using namespace hal::arch::io;

enum SerialPort : uint16_t {
    COM1 = 0x3F8
};

static bool transmitEmpty() {
    return (inb(COM1 + 5) & 0x20) != 0;
}

static void putc(const char c) {
    while (!transmitEmpty()) {
        asm volatile("pause");
    }
    outb(COM1, c);
}

void kprintf(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        putc(str[i]);
    }
}
