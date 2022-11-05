#pragma once

#include <cstdint>

#include "GDT.hpp"

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdt_ptr_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idt_ptr_t;

struct RegisterContext {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t err;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

namespace hal::arch::CPU {
struct CpuData {
    arch::GDT::Gdt gdt;
};

CpuData* thisCpu();

/**
 * Initialize current CPU.
 * Sets GDT, TSS, IDT and starts cpu-local devices
 */
void InitializeCpu();

}  // namespace hal::arch::CPU
