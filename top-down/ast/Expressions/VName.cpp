
#include <ast/Expressions/VName.hpp>

#include <ast/Expressions/Expression.hpp>

#include <ast/Expressions/Literals/CharLiteral.hpp>
#include <ast/Expressions/Literals/BooleanLiteral.hpp>
#include <ast/Expressions/Literals/IntegerLiteral.hpp>
#include <ast/Expressions/Literals/RealLiteral.hpp>
#include <ast/Expressions/Literals/StringLiteral.hpp>

#include <ast/Expressions/FunctionCall.hpp>

#include <ast/Expressions/ArrayExpression.hpp>

#include <ast/Identifier.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    // T = (E) | ID | LIT | F_CALL
    VName::VName(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), expr(nullptr), bLit(nullptr), iLit(nullptr), rLit(nullptr), sLit(nullptr), fCall(nullptr) , ident(nullptr) {

        std::unique_ptr<lexer::Lexeme> curr = nullptr;
        lexer::LexemeType type;        

        switch(NextType(lex)) {
            case lexer::O_PAREN:
                consumeLexemeType(lex,lexer::O_PAREN);
                expr = new Expression(lex,table);
                consumeLexemeType(lex,lexer::C_PAREN);
                break;
            case lexer::CHAR:
                cLit = new CharLiteral(lex,table);
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
        if(expr != nullptr) return expr->Validate();
        
        if(bLit != nullptr) return bLit->Validate();
        if(iLit != nullptr) return iLit->Validate();
        if(rLit != nullptr) return rLit->Validate();
        if(sLit != nullptr) return sLit->Validate();

        if(fCall != nullptr) return fCall->Validate();

        if(ident != nullptr) return ident->Validate();

        if(array != nullptr) return array->Validate();

    }

    std::unique_ptr<hardware::Register> VName::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        if(expr != nullptr) return expr->GenerateCode(codeGen);
        
        if(bLit != nullptr) return bLit->GenerateCode(codeGen);
        if(iLit != nullptr) return iLit->GenerateCode(codeGen);
        if(rLit != nullptr) return rLit->GenerateCode(codeGen);
        if(sLit != nullptr) return sLit->GenerateCode(codeGen);

        if(fCall != nullptr) return fCall->GenerateCode(codeGen);

        if(ident != nullptr) return ident->GenerateCode(codeGen);

        if(array != nullptr) return array->GenerateCode(codeGen);
        return nullptr;
    }

    ValueType VName::ResultType() const {
        if(expr != nullptr) return expr->ResultType();
        
        if(bLit != nullptr) {
            return bLit->ResultType();
        }
        if(iLit != nullptr) return iLit->ResultType();
        if(rLit != nullptr) return rLit->ResultType();
        if(sLit != nullptr) return sLit->ResultType();

        if(fCall != nullptr) return fCall->ResultType();

        if(ident != nullptr) return ident->ResultType();

        if(array != nullptr) return array->ResultType();

        throw std::runtime_error("something went wrong");
    }

    std::ostream & VName::Write(std::ostream & os) const {
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
