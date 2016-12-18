
#ifndef RETURN_HPP_
#define RETURN_HPP_

#include <ast/Statements/Statement.hpp>

namespace ast {

    class Expression;

    class Return : public Statement {
        private:
            Expression* result = nullptr;
        public:
            Return(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~Return();
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

    };

}

#endif