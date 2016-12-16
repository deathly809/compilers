
#include <ast/Expressions/FunctionCall.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    FunctionCall::FunctionCall(lexer::Lexer& lex, symtable::SymbolTable * table ) : Ast(table), functionName(nullptr) {

        functionName = new Identifier(lex, table);
        consumeLexemeType(lex,lexer::O_PAREN);
        
        // arguments
        if(NextType(lex) != lexer::C_PAREN) {
            arguments.push_back(new Expression(lex, table));
            while(NextType(lex) == lexer::COMMA) {
                consumeLexemeType(lex,lexer::COMMA);
                arguments.push_back(new Expression(lex, table));
            }
        }
        consumeLexemeType(lex,lexer::C_PAREN);
    }

    FunctionCall::~FunctionCall() {
        delete functionName;
        for(auto && a : arguments) {
            delete a;
        }
    }

    void FunctionCall::Validate() const {
        for(auto && a : arguments) {
            a->Validate();
        }
    }

    void FunctionCall::GenerateCode(std::ostream & out) const {
    }

    ValueType FunctionCall::ResultType() const {
        return functionName->ResultType();
    }

    std::ostream& FunctionCall::Write(std::ostream & os) const {
        os << *functionName << "(";
        if(arguments.size() > 0) {
            os << *arguments[0];
            for(unsigned int i = 1; i < arguments.size(); ++i) {
                os << ", " << *arguments[i];
            }
        }
        return os << ")";
    }
}
