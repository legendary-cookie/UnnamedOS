#pragma once

#include <cstdint>

namespace hal::arch::GDT {
enum SegmentSelector : int8_t {
    Null,
    KernelCode,
    KernelData,
    UserCode,
    UserData,
    Tss
};

inline uint16_t EntryOffset(SegmentSelector selector) {
    return selector * 8;
}

struct Gdt {
    struct __attribute__((packed)) {
        uint16_t limit{ 0 };
        uint16_t base0{ 0 };
        uint8_t base1{ 0 };
        uint8_t access;
        uint8_t flags;
        uint8_t base2{ 0 };
    } gdtDescriptors[5];
} __attribute__((packed));

void Initialize(Gdt &gdt);
}  // namespace hal::arch::GDT
