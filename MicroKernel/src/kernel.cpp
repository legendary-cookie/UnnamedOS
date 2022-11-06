#include <hal.hpp>

extern "C" void kentry() {
    hal::Initialize();
    hal::Halt();
    while (1) {
    }
}
