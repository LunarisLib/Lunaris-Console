#pragma once

namespace Lunaris {
namespace Console {

#ifdef _WIN32
    enum class e_color { BLACK, DARK_BLUE, DARK_GREEN, DARK_AQUA, DARK_RED, DARK_PURPLE, GOLD, GRAY, DARK_GRAY, BLUE, GREEN, AQUA, RED, LIGHT_PURPLE, YELLOW, WHITE };
#else
    enum class e_color { BLACK, DARK_RED, DARK_GREEN, GOLD, DARK_BLUE, DARK_PURPLE, DARK_AQUA, GRAY, DARK_GRAY, RED, GREEN, YELLOW, BLUE, LIGHT_PURPLE, AQUA, WHITE };
#endif

} // namespace Console
} // namespace Lunaris