#pragma once

#include <mutex>

namespace Lunaris {
namespace Console {

    /**
     * @brief Get the global mutex used by both cout and print of this library
     * 
     * @return `std::unique_lock<std::mutex>` safe locked mutex
     */
    inline std::unique_lock<std::mutex> _get_global_stdout_mtx() {
        static std::mutex m;
        return std::unique_lock(m);
    }

    enum class e_color { BLACK, DARK_RED, DARK_GREEN, GOLD, DARK_BLUE, DARK_PURPLE, DARK_AQUA, GRAY, DARK_GRAY, RED, GREEN, YELLOW, BLUE, LIGHT_PURPLE, AQUA, WHITE };

} // namespace Console
} // namespace Lunaris