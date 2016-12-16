
#include <ast/Expressions/VName.hpp>

#include <ast/Expressions/Expression.hpp>

#include <ast/Expressions/BooleanLiteral.hpp>
#include <ast/Expressions/IntegerLiteral.hpp>
#include <ast/Expressions/RealLiteral.hpp>
#include <ast/Expressions/StringLiteral.hpp>

#include <ast/Expressions/FunctionCall.hpp>

#include <ast/Expressions/ArrayExpression.hpp>

#include <ast/Identifier.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

namespace ast {

    // T = (E) | ID | LIT | F_CALL
    VName::VName(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), expr(nullptr), bLit(nullptr), iLit(nullptr), rLit(nullptr), sLit(nullptr), fCall(nullptr) , ident(nullptr) {

        std::unique_ptr<lexer::Lexeme> curr = nullptr;
        lexer::LexemeType type;

        negate = false;
        while(NextType(lex) == lexer::MINUS) {
            negate = !negate;
            lex.Next();
            lex.HasNext();
        }

        while(NextType(lex) == lexer::PLUS) {
            lex.Next();
            lex.HasNext();
        }

        switch(NextType(lex)) {
            case lexer::O_PAREN:
                consumeLexemeType(lex,lexer::O_PAREN);
                expr = new Expression(lex,table);
                consumeLexemeType(lex,lexer::C_PAREN);
                break;
            case lexer::STRING:
                sLit = new StringLiteral(lex,table);
                break;
            case lexer::INT:
                iLit = new IntegerLiteral(lex,table);
                break;
            case lexer::REAL:
                rLit = new RealLiteral(lex,table);
                break;
            case lexer::ID:
                curr = lex.Next();
                lex.HasNext();
                
                type = NextType(lex);
                
                lex.PushBack(curr);
                if(type == lexer::O_PAREN) {
                    fCall = new FunctionCall(lex, table);
                } else if(type == lexer::O_BRACKET) {
                    array = new ArrayExpression(lex, table);
                } else {
                    ident = new Identifier(lex,table);
                }

                break;
            case lexer::BOOL:
                bLit = new BooleanLiteral(lex,table);
                break;
            default:
                throw std::runtime_error("should we really be here");
                /* nothing */
                break;
        }
    }

    VName::~VName() {
        delete expr;

        delete bLit;
        delete iLit;
        delete rLit;
        delete sLit;

        delete fCall;

        delete ident;
    }

    void VName::Validate() const {
        if(expr != nullptr) expr->Validate();
        if(negate) {
            switch(ResultType()) {
                case StringType:
                    throw std::runtime_error("cannot negate a string");
                default:
                    break;
            }            
        }
    }

    void VName::GenerateCode(std::ostream & out) const {
        // TODO : Generate the code!
    }

    ValueType VName::ResultType() const {
        if(expr != nullptr) return expr->ResultType();
        
        if(bLit != nullptr) return bLit->ResultType();
        if(iLit != nullptr) return iLit->ResultType();
        if(rLit != nullptr) return rLit->ResultType();
        if(sLit != nullptr) return sLit->ResultType();

        if(fCall != nullptr) return fCall->ResultType();

        if(ident != nullptr) return ident->ResultType();

        if(array != nullptr) return array->ResultType();

        throw std::runtime_error("something went wrong");
    }

    std::ostream & VName::Write(std::ostream & os) const {
        if(negate) os << "-";
        if(expr != nullptr) os << *expr;
        else if(bLit != nullptr) os << *bLit;
        else if(iLit != nullptr) os << *iLit;
        else if(rLit != nullptr) os << *rLit;
        else if(sLit != nullptr) os << *sLit;
        else if(fCall != nullptr) os << *fCall;
        else if(ident != nullptr) os << *ident;
        else if(array != nullptr) os << *array;
        return os;
    }

}
