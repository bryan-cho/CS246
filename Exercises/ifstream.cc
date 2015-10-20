#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("sample.txt");
    std::string s;
    while (file >> s) {
        std::cout << s << std::endl;
    }
}
