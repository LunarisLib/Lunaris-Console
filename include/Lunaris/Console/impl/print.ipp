#include <format>

/**
 * @brief Make enum of colors translatable to internal std::vformat
 */
template <>
struct std::formatter<Lunaris::Console::e_color> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(Lunaris::Console::e_color color, std::format_context& ctx) const {            
        const auto color_u = static_cast<uint8_t>(color);
        const int code = color_u >= 8 ? (color_u + 90 - 8) : (color_u + 30);
        return std::format_to(ctx.out(), "\033[{}m", code);
    }
};

namespace Lunaris {
namespace Console {

    template<typename... Args>
    inline void mprint(const std::string_view fmt, Args&&... args) {
        const auto hold_lock = _get_global_stdout_mtx();
        std::cout << std::vformat(fmt, std::make_format_args(args...)) << std::format("{}", e_color::GRAY);
    }

    template<typename... Args>
    inline void mprint(const std::locale& loc, const std::string_view fmt, Args&&... args) {
        const auto hold_lock = _get_global_stdout_mtx();
        std::cout << std::vformat(loc, fmt, std::make_format_args(args...)) << std::format("{}", e_color::GRAY);
    }

    template<typename... Args>
    inline void mprintln(const std::string_view fmt, Args&&... args) {
        const auto hold_lock = _get_global_stdout_mtx();
        std::cout << std::vformat(fmt, std::make_format_args(args...)) << std::format("{}\n", e_color::GRAY);
    }

    template<typename... Args>
    inline void mprintln(const std::locale& loc, const std::string_view fmt, Args&&... args) {
        const auto hold_lock = _get_global_stdout_mtx();
        std::cout << std::vformat(loc, fmt, std::make_format_args(args...)) << std::format("{}\n", e_color::GRAY);
    }

} // namespace Console
} // namespace Lunaris