
#ifndef IDENTIFIER_HPP_
#define IDENTIFIER_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

#include <memory>

namespace lexer {
    class Lexeme;
}

namespace ast {

    class Identifier : public Ast {
        public:
            Identifier(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~Identifier();
            
            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;

            ValueType ResultType() const;
            std::string GetName() const;

            friend std::ostream& operator<<(std::ostream & os, const Identifier & id);

        private:
            std::unique_ptr<lexer::Lexeme> lexeme;

    };

    std::ostream& operator<<(std::ostream & os, const Identifier & id);

}

#endif
