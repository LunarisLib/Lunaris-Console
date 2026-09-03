#pragma once

#include <string_view>
#include <iostream>

#include <Lunaris/Console/common.h>

namespace Lunaris {
namespace Console {

    /**
     * @brief Print text safely with internal mutex for parallel calls
     * 
     * Internally, vformat() is used, so, format text with the new {} standard
     * 
     * @param fmt String format
     * @param args Arguments, if any, to replace in format
     */
    template<typename... Args>
    void mprint(const std::string_view fmt, Args&&... args);

    /**
     * @brief Print text safely with internal mutex for parallel calls plus locale
     * 
     * Internally, vformat() is used, so, format text with the new {} standard
     * 
     * @param locale Locale format
     * @param fmt String format
     * @param args Arguments, if any, to replace in format
     */
    template<typename... Args>
    void mprint(const std::locale& loc, const std::string_view fmt, Args&&... args);
    
    /**
     * @brief Print text safely with internal mutex for parallel calls and automatic newline
     * 
     * Internally, vformat() is used, so, format text with the new {} standard
     * 
     * @param fmt String format
     * @param args Arguments, if any, to replace in format
     */
    template<typename... Args>
    void mprintln(const std::string_view fmt, Args&&... args);

    /**
     * @brief Print text safely with internal mutex for parallel calls and automatic newline plus locale
     * 
     * Internally, vformat() is used, so, format text with the new {} standard
     * 
     * @param locale Locale format
     * @param fmt String format
     * @param args Arguments, if any, to replace in format
     */
    template<typename... Args>
    void mprintln(const std::locale& loc, const std::string_view fmt, Args&&... args);
    

} // namespace Console
} // namespace Lunaris

#include <Lunaris/Console/impl/print.ipp>