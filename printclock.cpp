#include <chrono>
#include <iostream>

int
main()
{
    using Clock = std::chrono::high_resolution_clock;
    constexpr auto num = Clock::period::num;
    constexpr auto den = Clock::period::den;
    std::cout << Clock::now().time_since_epoch().count()
              << " [" << num << '/' << den << "] units since epoch\n";
}

