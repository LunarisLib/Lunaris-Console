#include <iostream>
#include <streambuf>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <functional>
#include <random>

inline std::string generate_random_string(size_t size)
{
    constexpr std::string_view characters = "0123456789abcdefhijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-=+-*/@!~\\/$% ";
    constexpr size_t characters_len = characters.length();

    std::string str(size, '\0');
    std::random_device rd; 
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, characters_len-1);

    for(auto& ch : str) {
        ch = characters[distrib(gen)];
    }

    return str;
}

template <typename Logger, std::size_t... Is>
void chain_vector_impl(Logger& logger, const std::vector<std::string>& vec, std::index_sequence<Is...>) {
    // Expands to: logger << vec[0] << vec[1] << vec[2] ... << vec[N-1];
    (logger << ... << vec[Is]);
}

template <std::size_t N, typename Logger>
void chain_vector(Logger& logger, const std::vector<std::string>& vec)
{
    chain_vector_impl(logger, vec, std::make_index_sequence<N>{});
}




// Struct to store chunks of output and who wrote them
struct OutputEvent {
    std::thread::id thread_id;
    std::string text;
};

class ThreadSnifferBuf : public std::streambuf {
    std::mutex mtx;
    std::vector<OutputEvent>& event_log;

public:
    ThreadSnifferBuf(std::vector<OutputEvent>& log) : event_log(log) {}

protected:
    virtual std::streamsize xsputn(const char_type* s, std::streamsize count) override {
        std::lock_guard<std::mutex> lock(mtx);
        event_log.push_back({std::this_thread::get_id(), std::string(s, count)});
        return count;
    }

    virtual int_type overflow(int_type c) override {
        if (c != traits_type::eof()) {
            char_type ch = traits_type::to_char_type(c);
            std::lock_guard<std::mutex> lock(mtx);
            event_log.push_back({std::this_thread::get_id(), std::string(1, ch)});
        }
        return c;
    }
};

class ScopedCoutSniffer {
    std::streambuf* old_buf;
    ThreadSnifferBuf custom_buf;

public:
    ScopedCoutSniffer(std::vector<OutputEvent>& log)
        : custom_buf(log), old_buf(std::cout.rdbuf(&custom_buf)) {}

    ~ScopedCoutSniffer() {
        std::cout.rdbuf(old_buf);
    }
};

inline std::vector<OutputEvent> capture_block(std::function<void()> to_run) {
    std::vector<OutputEvent> out;
    ScopedCoutSniffer cbr(out);
    to_run();
    return out;
}