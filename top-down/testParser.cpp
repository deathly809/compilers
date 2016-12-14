
#include <iostream>

#include <Lexer.hpp>
#include <Parser.hpp>

#include <Node.hpp>

void printSpaces(int N) {
    if(N > 0) {
        std::cout << "  ";
        printSpaces(N - 1);
    }
}

void print(parser::Node* root,int height = 0) {

    if(root != nullptr) {

        print(root->GetLeft(),height + 1);
        printSpaces(height);

        std::cout << *root << std::endl;

        print(root->GetRight(),height + 1);

    }
}

int main(int argc, char* argv[]) {
    try {
        lexer::Lexer *lex = new lexer::Lexer(argv[1]);
        parser::Parser* par = new parser::Parser(lex);
        parser::Node* root = par->Parse();
        print(root);
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}