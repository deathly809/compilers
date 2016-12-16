
#include <ast/Expressions/Term.hpp>

#include <ast/Expressions/Expression.hpp>

#include <ast/Expressions/BooleanLiteral.hpp>
#include <ast/Expressions/IntegerLiteral.hpp>
#include <ast/Expressions/RealLiteral.hpp>
#include <ast/Expressions/StringLiteral.hpp>

#include <ast/Expressions/FunctionCall.hpp>

#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    // T := (E) | ID | LIT | F_CALL
    Term::Term(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), expr(nullptr), bLit(nullptr), iLit(nullptr), rLit(nullptr), sLit(nullptr), fCall(nullptr) , ident(nullptr) {

        std::unique_ptr<lexer::Lexeme> curr = nullptr;
        lexer::LexemeType type;
        
        switch(NextType(lex)) {
            case lexer::O_PAREN:
                consumeLexemeType(lex.Next(),lexer::O_PAREN);
                lex.HasNext();
                expr = new Expression(lex,table);
                consumeLexemeType(lex.Next(),lexer::C_PAREN);
                lex.HasNext();
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
                if(type != lexer::O_PAREN) {
                    ident = new Identifier(lex,table);
                } else {
                    fCall = new FunctionCall(lex, table);
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

    Term::~Term() {
        delete expr;

        delete bLit;
        delete iLit;
        delete rLit;
        delete sLit;

        delete fCall;

        delete ident;
    }

    void Term::Validate() const {
        if(expr != nullptr) expr->Validate();
    }

    void Term::GenerateCode(std::ostream & out) const {
        // TODO : Generate the code!
    }

    ValueType Term::ResultType() const {
        if(expr != nullptr) return expr->ResultType();
        
        if(bLit != nullptr) return bLit->ResultType();
        if(iLit != nullptr) return iLit->ResultType();
        if(rLit != nullptr) return rLit->ResultType();
        if(sLit != nullptr) return sLit->ResultType();

        if(fCall != nullptr) return fCall->ResultType();

        if(ident != nullptr) return ident->ResultType();

        throw std::runtime_error("something went wrong");
    }

    std::ostream & operator<<(std::ostream & os, const Term & term) {
        if(term.expr != nullptr) os << *term.expr;
        else if(term.bLit != nullptr) os << *term.bLit;
        else if(term.iLit != nullptr) os << *term.iLit;
        else if(term.rLit != nullptr) os << *term.rLit;
        else if(term.sLit != nullptr) os << *term.sLit;
        else if(term.fCall != nullptr) os << *term.fCall;
        else if(term.ident != nullptr) os << *term.ident;
        return os;
    }

}
