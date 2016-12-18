
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
            virtual std::unique_ptr<hardware::Register> GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;
            std::string GetName() const;

            std::string GetFilename() const;
            int GetColumn() const;
            int GetLine() const;
            
        private:
            std::unique_ptr<lexer::Lexeme> lexeme;

    };

}

#endif
