#pragma once

#include <type_traits>
#include <mutex>

#include <Lunaris/Console/common.h>

namespace Lunaris {
namespace Console {

    class Console {
        class console_ctl;
    public:
		template<typename T>
		const console_ctl operator<<(const T& arg);

        const console_ctl no_line();
    private:
		std::mutex m_safe;

        class console_ctl {
        public:
            ~console_ctl();

            const console_ctl& operator<<(const e_color& color) const;

            template<typename T, typename = std::enable_if_t<!std::is_same_v<std::decay<T>, e_color>, int>>
            const console_ctl& operator<<(const T& arg) const;
        private:
            console_ctl(console_ctl&&);
            console_ctl(std::unique_lock<std::mutex>&& lock, const bool new_line = true);
            
			std::unique_lock<std::mutex> m_lock_safe;
            const bool m_new_liner{ true };

            friend class Console;
        };        
    };

    inline Console cout;

} // namespace Console
} // namespace Lunaris

#include <Lunaris/Console/impl/cout.ipp>