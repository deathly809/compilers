

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <lexer/Scanner.hpp>

#include <iostream>
#include <string>
#include <vector>

#include <memory>

namespace lexer {

    class Lexeme;

    class Lexer {

        public:
            Lexer(std::string);
            Lexer(Scanner*);
            ~Lexer();
            bool HasNext();
            void PushBack(std::unique_ptr<Lexeme> & lex);
            std::unique_ptr<Lexeme> Next();

        private:
            int line,column;
            std::string file;
            Scanner* scan;

            std::vector<std::unique_ptr<Lexeme>> pushedBack;

            std::unique_ptr<Lexeme> readIdentifier();
            std::unique_ptr<Lexeme> readNumber();
            std::unique_ptr<Lexeme> readString();
            std::unique_ptr<Lexeme> readCharacter();
            //std::unique_ptr<Lexeme> readReal();
            
    };

}

#endif
