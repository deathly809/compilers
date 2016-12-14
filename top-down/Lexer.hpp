

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <Scanner.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace lexer {

    class Lexeme;

    class Lexer {

        public:
            Lexer(std::string);
            Lexer(Scanner*);
            ~Lexer();
            bool HasNext();
            void PushBack(Lexeme* lex);
            Lexeme* Next();

        private:
            int line,column;
            std::string file;
            Scanner* scan;

            std::vector<Lexeme*> pushedBack;

            Lexeme* readIdentifier();
            Lexeme* readNumber();
            
    };

}

#endif