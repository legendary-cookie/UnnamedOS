#pragma once

#include <cstdint>

#include "CPU.hpp"

typedef struct {
    uint16_t base_low;
    uint16_t sel;
    uint8_t ist;
    uint8_t flags;
    uint16_t base_med;
    uint32_t base_high;
    uint32_t null;
} __attribute__((packed)) idt_entry_t;

typedef void (*isr_t)(void*, RegisterContext*);

namespace hal::arch::IDT {
void Initialize();
void RegisterIntHandler(uint8_t intterupt, isr_t handler);
}  // namespace hal::arch::IDT
