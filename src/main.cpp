#include <iostream>
#include <tuple>

int main() {
    auto foo = std::make_tuple("bar", "foo", "can");
    std::cout << std::get<0>(foo) << std::get<1>(foo) << std::get<2>(foo);
} 

