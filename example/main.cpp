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

    mprintln("This is a {0}{1}{2} test that tests {3} like '{4}' directly, like rounding pi to {5:.2} instead of {5:.6}!", e_color::GOLD, "print", e_color::GRAY, "replacing values", 621, 3.1415f);
    return 0;
}

