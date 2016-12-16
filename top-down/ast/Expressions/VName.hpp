
#ifndef VNAME_HPP_
#define VNAME_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace ast {

    class Expression;
    class BooleanLiteral;
    class IntegerLiteral;
    class RealLiteral;
    class StringLiteral;
    class FunctionCall;
    class Identifier;

    class VName : public Ast {

        public:
            VName(lexer::Lexer & lex,symtable::SymbolTable * table);
            ~VName();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:

            Expression*     expr = nullptr;

            BooleanLiteral* bLit = nullptr;
            IntegerLiteral* iLit = nullptr;
            RealLiteral*    rLit = nullptr;
            StringLiteral*  sLit = nullptr;

            FunctionCall*   fCall = nullptr;

            Identifier*     ident = nullptr;

            bool            negate = false;

            
    };

}

#endif