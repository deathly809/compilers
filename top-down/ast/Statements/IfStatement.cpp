
#include <ast/Statements/IfStatement.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Block.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    IfStatement::IfStatement(lexer::Lexer & lex, symtable::SymbolTable * table) : Statement(table) {
        consumeLexemeType(lex.Next(), lexer::IF);
        cond = new Expression(lex, table);
        trueBlock = new Block(lex, table);
        if(lex.Next()->GetType() == lexer::ELSE) {
            consumeLexemeType(lex.Next(), lexer::ELSE);
            falseBlock = new Block(lex, table);
        }
    }

    IfStatement::~IfStatement() {
        delete cond;
        delete trueBlock;
        delete falseBlock;
    }

    void IfStatement::Validate() {
        cond->Validate();
        trueBlock->Validate();
        if(falseBlock != nullptr) {
            falseBlock->Validate();
        }
    }

    void IfStatement::GenerateCode(std::ostream & out) {

    }

}