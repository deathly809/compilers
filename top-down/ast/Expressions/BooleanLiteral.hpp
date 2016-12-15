
#ifndef BOOLEANLITERAL_HPP_
#define BOOLEANLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace ast {

    class BooleanLiteral : public Ast {

        public:
            BooleanLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;

            ValueType ResultType() const;
            bool  GetValue() const;

        private:
            bool value;

    };

        std::ostream& operator<<(std::ostream& os, const BooleanLiteral & bLit);
}

#endif