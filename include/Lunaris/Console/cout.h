#pragma once

#include <type_traits>
#include <mutex>

#include <Lunaris/Console/common.h>

namespace Lunaris {
namespace Console {

    /**
     * @brief This is a mimic of std::cout with extra safety in mind + colors support
     */
    class Console {
        class console_ctl;
    public:
        /**
         * @brief Classic << operator cout style. Prints next and hold mutex by temporary object
         * 
         * @param arg Next argument to print
         * @return `const console_ctl` safe block handle
         */
		template<typename T>
		const console_ctl operator<<(const T& arg);

        const console_ctl no_line();
    private:
        class console_ctl {
        public:
            ~console_ctl();

            /**
             * @brief Classic << operator cout style. Prints next and hold mutex by temporary object
             * 
             * @param arg Next argument to print
             * @return `const console_ctl&` self block handle
             */
            const console_ctl& operator<<(const e_color& color) const;

            /**
             * @brief Classic << operator cout style. Prints next and hold mutex by temporary object
             * 
             * @param arg Next argument to print
             * @return `const console_ctl&` self block handle
             */
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