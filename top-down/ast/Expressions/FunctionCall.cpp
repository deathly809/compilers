
#include <ast/Expressions/FunctionCall.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    FunctionCall::FunctionCall(lexer::Lexer& lex, symtable::SymbolTable * table ) : Ast(table), functionName(nullptr) {

        functionName = new Identifier(lex, table);
        
        std::unique_ptr<lexer::Lexeme> l = lex.Next();
        consumeLexemeType(l,lexer::O_PAREN);
        lex.HasNext();
        
        // arguments
        if(NextType(lex) != lexer::C_PAREN) {
            arguments.push_back(new Expression(lex, table));
            while(NextType(lex) == lexer::COMMA) {
                consumeLexemeType(lex.Next(),lexer::COMMA);

                lex.HasNext();
                arguments.push_back(new Expression(lex, table));
            }
        }
        consumeLexemeType(lex.Next(),lexer::C_PAREN);
        lex.HasNext();
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

    std::ostream& operator<<(std::ostream & os, const FunctionCall & fCall) {
        os << *fCall.functionName << "(";
        if(fCall.arguments.size() > 0) {
            os << *fCall.arguments[0];
            for(unsigned int i = 1; i < fCall.arguments.size(); ++i) {
                os << ", " << *fCall.arguments[i];
            }
        }
        return os << ")";
    }
}
