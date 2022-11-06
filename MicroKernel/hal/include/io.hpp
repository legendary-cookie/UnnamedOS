#pragma once

#include <cstdint>

namespace hal::io {
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
}  // namespace hal::io
