
#include <ast/Statements/Loop.hpp>

#include <ast/Statements/LoopCondition.hpp>
#include <ast/Block.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    Loop::Loop(lexer::Lexer& lex, symtable::SymbolTable * table) : Statement(table) {
        consumeLexemeType(lex.Next(),lexer::LOOP);
        if(lex.Next()->GetType() != lexer::O_BRACE ) {
            cond = new LoopCondition(lex, table);
        }
        block = new Block(lex, table);
    }

    Loop::~Loop() {
        delete cond;
        delete block;
    }

    void Loop::Validate() {
        cond->Validate();
        block->Validate();
    }

    void Loop::GenerateCode(std::ostream & out) {
        
    }

}