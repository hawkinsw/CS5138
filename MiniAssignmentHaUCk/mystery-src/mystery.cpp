#include <iostream>
#include <string>

int main() {
#ifndef W
    std::string output{"Emojis make me smile.\n"};
    std::cout << output << "\n";
#else
    const char16_t *output = u"Emojis make me smile.\n";
    std::cout << output << "\n";
#endif
    return 0;
}