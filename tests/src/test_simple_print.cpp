#include "commoh.h"
#include <cstring>
#include <set>
#include <thread>
#include <atomic>

#include <Lunaris/console.h>

using namespace Lunaris::Console;

constexpr size_t string_length = 1 << 15;
constexpr size_t num_of_threads = 128;

int main() {
    const auto log = capture_block([]{
        std::atomic<bool> waiter{true};
        std::atomic<size_t> ready_count{0};
        std::vector<std::thread> running_parallel{};

        const auto fcn_parallel = [&] {
            const auto big_string = generate_random_string(string_length);
            
            ++ready_count;
            while(waiter) std::this_thread::yield();

            mprint("{}{}{}{}", big_string, big_string, big_string, big_string);

            --ready_count;
        };

        std::printf("Spawning %zu threads, each generating a string of length = %zu...\n", num_of_threads, string_length);

        for(size_t k = 0; k < num_of_threads; ++k) {
            running_parallel.push_back(std::thread(fcn_parallel));
        }

        std::printf("Waiting all to be ready...\n");

        while(ready_count != num_of_threads) std::this_thread::sleep_for(std::chrono::milliseconds(20));

        std::printf("Concurrency START!\n");
        waiter = false;

        while(ready_count != 0) std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::printf("Concurrency END!\n");
        
        for(auto& i : running_parallel) i.join();
    });

    mprintln("Checking results...");

    std::set<std::thread::id> context_switch_counter;
    std::thread::id last_id = log.size() ? log[0].thread_id : std::thread::id{};
    bool got_issue = false;

    for (const auto& event : log) {
        if (event.thread_id != last_id && !context_switch_counter.emplace(event.thread_id).second)
            got_issue = true;

        last_id = event.thread_id;

        //std::printf("[Debug] [Thread %X] wrote: %s\n", event.thread_id, event.text.c_str());
    }
    
    if (got_issue) {
        std::printf("Concurrency is a problem.\n");
        return 1;
    }
    mprintln("{}Concurrency went great!", e_color::GREEN);

    return 0;
}