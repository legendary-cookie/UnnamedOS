#pragma once

#include <cstdint>

// TODO: Move to proper mm namespace
enum PageSize : uint32_t {
    Size4K = 0x00001000,
    Size2M = 0x00200000,
    Size1G = 0x40000000,
};

namespace hal {
/**
 * Halt the CPU
 */
void Halt();

/**
 * Initialize the CPU
 * and other arch specific things
 */
void Initialize();

/**
 * Sleep for usec
 * On x86, for example
 * the HPET is used
 */
void Usleep(uint64_t usec);
}  // namespace hal
