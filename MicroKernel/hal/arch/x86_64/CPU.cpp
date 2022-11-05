#include "CPU.hpp"

namespace hal::arch::CPU {
CpuData tmpInstance;

CpuData* thisCpu() {
    return &tmpInstance;
}
}  // namespace hal::arch::CPU
