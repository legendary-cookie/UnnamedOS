#include "CPU.hpp"

#include "GDT.hpp"
#include "IDT.hpp"

namespace hal::arch::CPU {
using namespace hal::arch;

CpuData tmpInstance;

CpuData* thisCpu() {
    return &tmpInstance;
}

void InitializeCpu() {
    GDT::Initialize(CPU::thisCpu()->gdt);
    IDT::Initialize();
}

}  // namespace hal::arch::CPU
