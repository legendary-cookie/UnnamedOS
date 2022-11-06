#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <io.hpp>

namespace drivers {

enum Port : uint16_t {
    COM1 = 0x3F8
};

class SerialPort {
private:
    Port port;

    inline bool transmitEmpty() const noexcept {
        return hal::io::inb(port + 5) & 0x20;
    }

public:
    SerialPort(Port _port)
        : port(_port){};

    void write(const char c) const {
        hal::io::outb(port, c);
    }

    void write(const char* s, int len) const {
        if (len == -1) {
            len = strlen(s);
        }

        for (int i = 0; i < len; ++i) {
            write(s[i]);
        }
        write('\0');
    }
};
}  // namespace drivers
