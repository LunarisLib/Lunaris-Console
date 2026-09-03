#include <iostream>
#include <vector>
#include <cstdint>
#include <random>

#include <Lunaris/console.h>

using namespace Lunaris::Console;

int main() {
    std::cout << "Base color of std::cout.\n";
    cout << e_color::AQUA << "Hello world!";
    cout << e_color::BLUE << "This is a simple test!";
    cout << "All went good?";
    return 0;
}

