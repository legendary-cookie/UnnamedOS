#include <hal.hpp>

extern "C" void kentry() {
	hal::Halt();
}
