
#include <ast/VariableBlock.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    VariableBlock::VariableBlock(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        consumeLexemeType(lex.Next(),lexer::VAR);
        consumeLexemeType(lex.Next(),lexer::O_PAREN);
        lexer::Lexeme* l = lex.Next();
        while(l->GetType() != lexer::C_PAREN) {
            vars.push_back(
                {
                    new Identifier(lex, table),
                    new Expression(lex, table)
                });
            l = lex.Next();
        }
        consumeLexemeType(lex.Next(),lexer::C_PAREN);
    }

    VariableBlock::~VariableBlock() {
        for( auto&& v : vars ) {
            delete v.lhs;
            delete v.rhs;
        }
        vars.clear();
    }

    void VariableBlock::Validate() {
        for( auto&& v : vars ) {
            v.lhs->Validate();
            v.rhs->Validate();
        }
    }

    void VariableBlock::GenerateCode(std::ostream & out) {

    }

}