
#ifndef IDENTIFIER_HPP_
#define IDENTIFIER_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace lexer {
    class Lexeme;
}

namespace ast {

    class Identifier : public Ast {
        lexer::Lexeme* lexeme;
        public:
            Identifier(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~Identifier();
            
            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;

            ValueType ResultType() const;
            std::string GetName() const;

            friend std::ostream& operator<<(std::ostream & os, const Identifier & id);
    };

    std::ostream& operator<<(std::ostream & os, const Identifier & id);

}

#endif
