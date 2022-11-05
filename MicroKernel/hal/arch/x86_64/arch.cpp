#include <hal.hpp>

namespace hal {
	void Halt() {
		asm volatile("cli; hlt");
	}
}
