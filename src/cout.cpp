#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

#include <Lunaris/Console/cout.h>

namespace Lunaris {
namespace Console {

    const Console::console_ctl Console::no_line() {
        Console::console_ctl ctl(_get_global_stdout_mtx(), false);
        return ctl;
    }

    Console::console_ctl::~console_ctl() {
        *this << e_color::GRAY;
        if (m_new_liner) std::cout << std::endl;
    }

    const Console::console_ctl& Console::console_ctl::operator<<(const e_color& color) const {
        const auto color_u = static_cast<uint8_t>(color);
		std::cout
            << "\033["
            << (color_u >= 8 ? (color_u + 90 - 8) : (color_u + 30))
            << "m";
        return *this;
    }

    Console::console_ctl::console_ctl(console_ctl&& oth) 
        : m_lock_safe(std::move(oth.m_lock_safe)), m_new_liner(oth.m_new_liner)
    {}

    Console::console_ctl::console_ctl(std::unique_lock<std::mutex>&& lock, const bool new_line)
        : m_lock_safe(std::move(lock)), m_new_liner(new_line)
    {}

} // namespace Console
} // namespace Lunaris