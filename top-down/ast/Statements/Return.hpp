
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
            
            virtual void Validate();
            virtual void GenerateCode(std::ostream & out);
    };

}

#endif