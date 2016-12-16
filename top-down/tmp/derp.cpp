
#include <lexer/Lexer.hpp>
#include <lexer/Lexeme.hpp>

#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if(argc == 2) {
        std::string input(argv[1]);
        std::stringstream  ss;
        ss << input;
        Scanner* scan = new Scanner(ss);
        lexer::Lexer lex(scan);

        while(lex.HasNext()) {
            auto ptr = lex.Next();
            std::cout << *ptr << std::endl;
        }
    }
    return 0;
}
