#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <getopt.h>

void process_options(int argc, char *argv[]);
struct Config {
    Config()
        :number_to_generate{10},
        json_output{false} {
    }
    size_t number_to_generate;
    bool json_output;
} config;

int main(int argc, char *argv[]) {
    process_options(argc, argv);
    //std::cout << "Generating " << config.number_to_generate << " ip addresses\n";

    srand(time(nullptr));
    for(size_t i = 0; i < config.number_to_generate; ++i) {
        uint8_t one = rand() % 250;
        uint8_t two = rand() % 250;
        uint8_t three = rand() % 250;
        uint8_t four = rand() % 250;
        if(one == 192 || one == 172 || one == 10 || one == 224) {
            // We don't want private or multicast
            ++config.number_to_generate;
            continue;
        }

        if(config.json_output) {
            std::ostringstream os;
            os << "{\"endpoint\":\"region\",\"ip_addr\":\"" << (int)one << "." << (int)two << "." << (int)three << "." << (int)four << "\"}";
            std::cout << os.str().length() << std::endl << os.str() << std::endl;
        } else {
            std::cout << (int)one << "." << (int)two << "." << (int)three << "." << (int)four << std::endl;
        }
    }
    return 0;
}

void process_options(int argc, char *argv[])
{
    while(true) {
        static option long_options[] = {
            {"help",  no_argument,       nullptr, 'h'},
            {"json",  no_argument,       nullptr, 'j'},
            {"count", required_argument, nullptr, 'c'},
            {nullptr, 0,                 nullptr, 0}
        };
        int option_index = 0;
        int opt = getopt_long(argc, argv, "hjc:", long_options, &option_index);
        if(opt == -1) {
            break;
        }
        switch(opt) {
            case 'c':
                try {
                    config.number_to_generate = std::stoul(optarg);
                } catch(const std::exception &e) {
                    std::cerr << "Cannot convert '" << optarg << "' to integer" << std::endl;
                    exit(1);
                }
            break;

            case 'j':
                config.json_output = true;
            break;
            
            case 'h':
            case '?':
            default:
                std::cout << (char)opt << " " << optind << std::endl;
                std::cout << "Usage: " << argv[0] << "\n";
                std::cout << " -h, --help               This help\n";
                std::cout << " -c, --count              Number of ip addresses to output (default 10)\n";
                std::cout << " -h, --json               Output in a json request format\n";
                exit(0);
                break;
        }
    }
}
