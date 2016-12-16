
#include <ast/Util.hpp>

#include <LexemeTypes.hpp>
#include <Lexeme.hpp>
#include <Lexer.hpp>

#include <memory>

namespace ast {

    void checkEOF(bool value) {
        if(!value) {
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", unexpected EOF");
        }
    }

        lexer::LexemeType NextType(lexer::Lexer & lex) {
            std::unique_ptr<lexer::Lexeme> l = lex.Next();
            lexer::LexemeType type = l->GetType();
            lex.PushBack(l);
            return type;
        }
    
}