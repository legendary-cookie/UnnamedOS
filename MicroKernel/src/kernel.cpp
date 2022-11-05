#include <hal.hpp>

#include "log.hpp"

extern "C" void kentry() {
    hal::Initialize();
    hal::Halt();
}
