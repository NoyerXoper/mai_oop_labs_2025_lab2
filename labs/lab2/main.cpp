#include <iostream>
#include <string>
#include <stdexcept>

#include "seven.hpp"


int main() {
    std::string str;
    std::cin >> str;
    try {
        Seven s(str);
        std::cout << "Well... You entered number... But I \"don't know\" operator overloading and I can't overload std::ostream& operator<<(std::ostream& stream, const Seven& obj).\n";
        std::cout << "BUT you can look at the address of Seven object: " << &s << "\n";
    } catch (const std::invalid_argument& exc) {
        std::cout << "You made a mistake: " << exc.what() << "\n";
    }

}