#pragma once

#include <cstdint>

enum PageSize : uint32_t {
    Size4K = 0x00001000,
    Size2M = 0x00200000,
    Size1G = 0x40000000,
};

namespace hal {
void Halt();

void Initialize();
}  // namespace hal
