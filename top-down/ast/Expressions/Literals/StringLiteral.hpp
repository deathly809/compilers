
#ifndef STRINGLITERAL_HPP_
#define STRINGLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>


namespace ast {

    class StringLiteral : public Ast {

        public:
            StringLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            virtual ValueType ResultType() const;
            std::string GetValue() const;

        private:
            std::string value;
    };


}

#endif