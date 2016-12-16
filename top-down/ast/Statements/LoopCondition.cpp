
#include <ast/Statements/LoopCondition.hpp>

#include <ast/Statements/InitStatement.hpp>
#include <ast/Expressions/Expression.hpp>
#include <ast/Statements/Assignment.hpp>

#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    // for {}
    // for cond {}
    // for init; cond; incr {}
    // problem: init can be assignment or variable definition
    // condition has to be exression
    LoopCondition::LoopCondition(lexer::Lexer& lex, symtable::SymbolTable * table ) : Ast(table), init(nullptr), cond(nullptr), incr(nullptr) {
        if(NextType(lex) != lexer::O_BRACE) {
            bool threeParts = false;

            if(NextType(lex) == lexer::VAR) {
                threeParts = true;
            } else {
                auto tmp = lex.Next();
                lex.HasNext();
                threeParts = NextType(lex) == lexer::EQUAL;
                lex.PushBack(tmp);
            }

            if(threeParts) {
                init = new InitStatement(lex, table);
                
                consumeLexemeType(lex.Next(),lexer::SEMI);
                lex.HasNext();

                cond = new Expression(lex, table);

                consumeLexemeType(lex.Next(),lexer::SEMI);
                lex.HasNext();
                
                incr = new Assignment(lex, table);
            } else {
                cond = new Expression(lex,table);
            }
        } 
    }

    LoopCondition::~LoopCondition() {
        delete init;
        delete cond;
        delete incr;
    }

    void LoopCondition::Validate() const {        
        if(init != nullptr) init->Validate();
        if(cond != nullptr) cond->Validate();
        if(incr != nullptr) incr->Validate();
    }

    void LoopCondition::GenerateCode(std::ostream & out) const {

    }

    std::ostream& LoopCondition::Write(std::ostream & os) const {
        if(init != nullptr) init->Write(os);
        if(cond != nullptr) os << "; " << *cond;
        if(incr != nullptr) os << "; " << *incr;
        return os;
    }

}