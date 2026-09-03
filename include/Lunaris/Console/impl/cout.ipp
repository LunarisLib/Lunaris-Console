#include <iostream>

namespace Lunaris {
namespace Console {

    template<typename T>
    const Console::console_ctl Console::operator<<(const T& arg) {
        Console::console_ctl ctl(_get_global_stdout_mtx());
        ctl << arg;
		return ctl;
    }

	template<typename T, typename>
	inline const Console::console_ctl& Console::console_ctl::operator<<(const T& arg) const
	{
		std::cout << arg;
		return *this;
	}

} // namespace Console
} // namespace Lunaris