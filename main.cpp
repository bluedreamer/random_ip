#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[])
{
    size_t number_to_generate = 10;
    if(argc > 1) {
        try {
            number_to_generate = std::stoul(argv[1]);
        } catch(const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    std::cout << "Generating " << number_to_generate << " ip addresses\n";

    srand(time(nullptr));
    for(size_t i = 0; i < number_to_generate; ++i) {
        uint8_t one = rand() % 250;
        uint8_t two = rand() % 250;
        uint8_t three = rand() % 250;
        uint8_t four = rand() % 250;
        if(one == 192 || one == 172 || one == 10 || one == 224) {
            // We don't want private or multicast
            ++number_to_generate;
            continue;
        }
        std::cout << (int)one << "." << (int)two << "." << (int)three << "." << (int)four << std::endl;
    }
    return 0;
}
