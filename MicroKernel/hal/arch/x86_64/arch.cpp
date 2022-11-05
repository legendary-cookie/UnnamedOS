#include <hal.hpp>

#include "CPU.hpp"
#include "GDT.hpp"
#include "IDT.hpp"
#include "limine.hpp"

alignas(uint16_t) static uint8_t stack[PageSize::Size4K * 2] = { 0 };

struct limine_memmap_request memmap {
    .id = LIMINE_MEMMAP_REQUEST, .revision = 0, .response = nullptr
};

namespace hal {
using namespace hal::arch;
void Halt() {
    asm volatile("cli; hlt");
}

void Initialize() {
    asm volatile("mov %0, %%rbp" ::"r"(stack)
                 : "memory");
    asm volatile("mov %0, %%rsp" ::"r"(stack + (PageSize::Size4K * 2))
                 : "memory");

    CPU::InitializeCpu();
}
}  // namespace hal
