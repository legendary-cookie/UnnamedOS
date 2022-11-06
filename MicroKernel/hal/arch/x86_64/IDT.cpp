#include "IDT.hpp"

#include <logger.hpp>

#include "CPU.hpp"

idt_entry_t idt[256];
idt_ptr_t idtPtr;

isr_t interruptHandlers[256];

extern uint64_t int_vectors[];

extern "C" {
void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();
void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();
}

namespace hal::arch::IDT {
static void SetGate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags, uint8_t ist = 0) {
    idt[num].base_high = (base >> 32);
    idt[num].base_med = (base >> 16) & 0xFFFF;
    idt[num].base_low = base & 0xFFFF;

    idt[num].sel = sel;
    idt[num].null = 0;
    idt[num].ist = ist & 0x7;  // Interrupt Stack Table (IST)

    idt[num].flags = flags;
}

void Initialize() {
    idtPtr.limit = sizeof(idt_entry_t) * 256 - 1;
    idtPtr.base = (uint64_t)&idt;

    for (int i = 0; i < 256; i++) {
        SetGate(i, 0, 0x08, 0x8E);
    }
    for (unsigned i = 48; i < 256; i++) {
        SetGate(i, int_vectors[i - 48], 0x08, 0x8E);
    }

    SetGate(0, (uint64_t)isr0, 0x08, 0x8E);
    SetGate(1, (uint64_t)isr1, 0x08, 0x8E);
    SetGate(2, (uint64_t)isr2, 0x08, 0x8E);
    SetGate(3, (uint64_t)isr3, 0x08, 0x8E);
    SetGate(4, (uint64_t)isr4, 0x08, 0x8E);
    SetGate(5, (uint64_t)isr5, 0x08, 0x8E);
    SetGate(6, (uint64_t)isr6, 0x08, 0x8E);
    SetGate(7, (uint64_t)isr7, 0x08, 0x8E);
    SetGate(8, (uint64_t)isr8, 0x08, 0x8E, 2);  // Double Fault
    SetGate(9, (uint64_t)isr9, 0x08, 0x8E);
    SetGate(10, (uint64_t)isr10, 0x08, 0x8E);
    SetGate(11, (uint64_t)isr11, 0x08, 0x8E);
    SetGate(12, (uint64_t)isr12, 0x08, 0x8E);
    SetGate(13, (uint64_t)isr13, 0x08, 0x8E);
    SetGate(14, (uint64_t)isr14, 0x08, 0x8E);
    SetGate(15, (uint64_t)isr15, 0x08, 0x8E);
    SetGate(16, (uint64_t)isr16, 0x08, 0x8E);
    SetGate(17, (uint64_t)isr17, 0x08, 0x8E);
    SetGate(18, (uint64_t)isr18, 0x08, 0x8E);
    SetGate(19, (uint64_t)isr19, 0x08, 0x8E);
    SetGate(20, (uint64_t)isr20, 0x08, 0x8E);
    SetGate(21, (uint64_t)isr21, 0x08, 0x8E);
    SetGate(22, (uint64_t)isr22, 0x08, 0x8E);
    SetGate(23, (uint64_t)isr23, 0x08, 0x8E);
    SetGate(24, (uint64_t)isr24, 0x08, 0x8E);
    SetGate(25, (uint64_t)isr25, 0x08, 0x8E);
    SetGate(26, (uint64_t)isr26, 0x08, 0x8E);
    SetGate(27, (uint64_t)isr27, 0x08, 0x8E);
    SetGate(28, (uint64_t)isr28, 0x08, 0x8E);
    SetGate(29, (uint64_t)isr29, 0x08, 0x8E);
    SetGate(30, (uint64_t)isr30, 0x08, 0x8E);
    SetGate(31, (uint64_t)isr31, 0x08, 0x8E);

    asm volatile("lidt %0;" ::"m"(idtPtr));

    SetGate(32, (uint64_t)irq0, 0x08, 0x8E);
    SetGate(33, (uint64_t)irq1, 0x08, 0x8E);
    SetGate(34, (uint64_t)irq2, 0x08, 0x8E);
    SetGate(35, (uint64_t)irq3, 0x08, 0x8E);
    SetGate(36, (uint64_t)irq4, 0x08, 0x8E);
    SetGate(37, (uint64_t)irq5, 0x08, 0x8E);
    SetGate(38, (uint64_t)irq6, 0x08, 0x8E);
    SetGate(39, (uint64_t)irq7, 0x08, 0x8E);
    SetGate(40, (uint64_t)irq8, 0x08, 0x8E);
    SetGate(41, (uint64_t)irq9, 0x08, 0x8E);
    SetGate(42, (uint64_t)irq10, 0x08, 0x8E);
    SetGate(43, (uint64_t)irq11, 0x08, 0x8E);
    SetGate(44, (uint64_t)irq12, 0x08, 0x8E);
    SetGate(45, (uint64_t)irq13, 0x08, 0x8E);
    SetGate(46, (uint64_t)irq14, 0x08, 0x8E);
    SetGate(47, (uint64_t)irq15, 0x08, 0x8E);
}

void RegisterIntHandler(uint8_t interrupt, isr_t handler) {
    interruptHandlers[interrupt] = handler;
}

}  // namespace hal::arch::IDT

extern "C" {
void irq_handler(uint8_t int_num, RegisterContext regs) {
}

void ipi_handler(uint8_t int_num, RegisterContext regs) {
}

void isr_handler(uint8_t int_num, RegisterContext regs) {
}
}
