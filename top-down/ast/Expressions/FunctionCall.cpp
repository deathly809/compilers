
#include <ast/Expressions/FunctionCall.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    FunctionCall::FunctionCall(lexer::Lexer& lex, symtable::SymbolTable * table ) : Ast(table) {
        functionName = new Identifier(lex, table);
        consumeLexemeType(lex.Next(),lexer::O_PAREN);
        lexer::Lexeme* l = lex.Next();
        if(l->GetType() != lexer::C_PAREN) {
            arguments.push_back(new Expression(lex, table));
            l = lex.Next();
            while(l->GetType() == lexer::COMMA) {
                consumeLexemeType(lex.Next(),lexer::COMMA);
                arguments.push_back(new Expression(lex, table));
                l = lex.Next();
            }
        } 
        consumeLexemeType(lex.Next(),lexer::C_PAREN);
    }

    FunctionCall::~FunctionCall() {
        delete functionName;
        for(auto && a : arguments) {
            delete a;
        }
    }

    void FunctionCall::Validate() {
        for(auto && a : arguments) {
            a->Validate();
        }
    }

    void FunctionCall::GenerateCode(std::ostream & out) {
    }

    ValueType FunctionCall::ResultType() {
        return functionName->ResultType();
    }

}
