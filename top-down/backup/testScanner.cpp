
#include <iostream>

#include <lexer/Scanner.hpp>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string inputFile(argv[1]);
    Scanner scan(inputFile);
    while(scan.HasNext()) {
        std::cout << scan.Next();
    }
    return 0;
}
