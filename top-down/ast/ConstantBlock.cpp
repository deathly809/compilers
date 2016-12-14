
#include <ast/ConstantBlock.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    ConstantBlock::ConstantBlock(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        
        consumeLexemeType(lex.Next(),lexer::VAR);
        consumeLexemeType(lex.Next(),lexer::O_PAREN);

        lexer::Lexeme* c = lex.Next();
        while(c->GetType() != lexer::C_PAREN) {
            vars.push_back(
                {
                    new Identifier(lex, table),
                    new Expression(lex, table)
                });
            c = lex.Next();
        }
        consumeLexemeType(lex.Next(),lexer::C_PAREN);
    }

    ConstantBlock::~ConstantBlock() {
        for( auto&& v : vars ) {
            delete v.lhs;
            delete v.rhs;
        }
        vars.clear();
    }

    void ConstantBlock::Validate() {
        for( auto&& v : vars ) {
            v.lhs->Validate();
            v.rhs->Validate();
        }
    }

    void ConstantBlock::GenerateCode(std::ostream & out) {
    }

}