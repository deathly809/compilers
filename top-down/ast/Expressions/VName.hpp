
#ifndef VNAME_HPP_
#define VNAME_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace ast {

    class ArrayExpression;
    class Expression;
    class CharLiteral;
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
            virtual std::unique_ptr<hardware::Register> GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            Expression*         expr = nullptr;

            CharLiteral*        cLit = nullptr;
            BooleanLiteral*     bLit = nullptr;
            IntegerLiteral*     iLit = nullptr;
            RealLiteral*        rLit = nullptr;
            StringLiteral*      sLit = nullptr;

            FunctionCall*       fCall = nullptr;

            ArrayExpression*    array = nullptr;
            Identifier*         ident = nullptr;

            bool                negate = false;

            
    };

}

#endif