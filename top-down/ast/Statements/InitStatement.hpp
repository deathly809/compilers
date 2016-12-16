
#ifndef INITSTATEMENT_HPP_
#define INITSTATEMENT_HPP_

#include <ast/Ast.hpp>

namespace symtable {
    class SymbolTable;
}

namespace lexer {
    class Lexer;
}

namespace ast {

    class VariableDeclaration;
    class Assignment;

    class InitStatement : public Ast {
        public:

            InitStatement(lexer::Lexer& lex, symtable::SymbolTable * sym);
            ~InitStatement();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & os) const;
            virtual std::ostream& Write(std::ostream & os) const;

        private:
            VariableDeclaration*    varDef = nullptr;
            Assignment*             assign = nullptr;
    };
}

#endif