#ifdef _WIN32

#include <Windows.h>

namespace Lunaris {
namespace Console {

    bool enable_windows_ansi() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return false;
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return false;
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        return SetConsoleMode(hOut, dwMode);
    }

    static const bool g_ansi_enabled = enable_windows_ansi();
    
} // namespace Console
} // namespace Lunaris

#endif