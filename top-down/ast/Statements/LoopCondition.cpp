
#include <ast/Statements/LoopCondition.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    LoopCondition::LoopCondition(lexer::Lexer& lex, symtable::SymbolTable * table ) : Ast(table) {
        lexer::Lexeme* c = lex.Next();
        if(c->GetType() != lexer::O_BRACE) {  
            exp.push_back(new Expression(lex, table));
            c = lex.Next();
            if (c->GetType() == lexer::SEMI) {
                exp.push_back(new Expression(lex, table));
                consumeLexemeType(lex.Next(),lexer::SEMI);
                exp.push_back(new Expression(lex, table));
                consumeLexemeType(lex.Next(),lexer::SEMI);
            }
        }
    }

    LoopCondition::~LoopCondition() {
        for( auto && e : exp ) {
            delete e;
        }
    }

    void LoopCondition::Validate() {
        
        if(exp.size() == 1) {
            
            if( exp[0]->ResultType() != BoolType) {
                throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", expected boolean expression");
            }
            exp[0]->Validate();

        } else if(exp.size() == 3) {
            
            if(exp[1]->ResultType() != BoolType) {
                throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", expected boolean expression");
            }
            exp[1]->Validate();
        }
            
    }

    void LoopCondition::GenerateCode(std::ostream & out) {

    }
}