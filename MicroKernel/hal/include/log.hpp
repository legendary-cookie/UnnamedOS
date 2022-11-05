#pragma once

void kprintf(const char* str);

inline void info(const char* str) {
    kprintf("[INFO] ");
    kprintf(str);
    kprintf("\n");
}
