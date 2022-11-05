#include "GDT.hpp"

#include <cstdint>

#include "CPU.hpp"

extern "C" void loadGDT(uint64_t);

namespace hal::arch::GDT {
static void setGdtEntry(Gdt& cpuGdt, uint64_t selectorIdx, uint8_t flags, uint8_t access) {
    cpuGdt.gdtDescriptors[selectorIdx].flags = flags;
    cpuGdt.gdtDescriptors[selectorIdx].access = access;
}

void Initialize(Gdt& gdt) {
    setGdtEntry(gdt, SegmentSelector::Null, 0, 0);
    setGdtEntry(gdt, SegmentSelector::KernelCode, 0xA2, 0x9A);
    setGdtEntry(gdt, SegmentSelector::KernelData, 0xA0, 0x92);
    setGdtEntry(gdt, SegmentSelector::UserCode, 0x20, 0xFA);
    setGdtEntry(gdt, SegmentSelector::UserData, 0x00, 0xF2);

    gdt_ptr_t gdtr;
    gdtr.limit = (sizeof(Gdt) + 5) - 1;
    gdtr.base = reinterpret_cast<uint64_t>(&gdt);

    loadGDT((uint64_t)&gdtr);
}
}  // namespace hal::arch::GDT
