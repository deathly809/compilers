

#include <iostream>

#include <Lexer.hpp>
#include <Lexeme.hpp>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    try {
        std::string inputFile(argv[1]);
        lexer::Lexer lex(inputFile);

        while(lex.HasNext()) {
            lexer::Lexeme* l = lex.Next();
            std::cout << *l << std::endl;
            delete l;
        }
        
    } catch(const std::exception& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
    return 0;
}