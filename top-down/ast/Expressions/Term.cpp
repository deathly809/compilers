
#include <ast/Expressions/Term.hpp>

#include <ast/Expressions/Expression.hpp>

#include <ast/Expressions/BooleanLiteral.hpp>
#include <ast/Expressions/IntegerLiteral.hpp>
#include <ast/Expressions/RealLiteral.hpp>
#include <ast/Expressions/StringLiteral.hpp>

#include <ast/Expressions/FunctionCall.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    // T := (E) | ID | LIT | F_CALL
    Term::Term(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        lexer::Lexeme *l = lex.Next();
        lex.PushBack(l);
        switch(l->GetType()) {
            case lexer::O_PAREN:
                consumeLexemeType(lex.Next(),lexer::O_PAREN);
                expr = new Expression(lex,table);
                consumeLexemeType(lex.Next(),lexer::O_PAREN);
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
                fCall = new FunctionCall(lex, table);
                break;
            default:
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
    }

    void Term::Validate() {
        if(expr != nullptr) expr->Validate();
    }

    void Term::GenerateCode(std::ostream & out) {
        // TODO : Generate the code!
    }

    ValueType Term::ResultType() {
        if(expr != nullptr) return expr->ResultType();
        
        if(bLit != nullptr) return bLit->ResultType();
        if(iLit != nullptr) return iLit->ResultType();
        if(rLit != nullptr) return rLit->ResultType();
        if(sLit != nullptr) return sLit->ResultType();

        if(fCall != nullptr) return fCall->ResultType();

        throw std::runtime_error("something went wrong");
    }

}
