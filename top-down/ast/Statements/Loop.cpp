
#include <ast/Statements/Loop.hpp>

#include <ast/Statements/LoopCondition.hpp>
#include <ast/Block.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    Loop::Loop(lexer::Lexer& lex, symtable::SymbolTable * table) : Statement(table) {
        consumeLexemeType(lex.Next(),lexer::LOOP);
        lex.HasNext();
        
        if(NextType(lex) != lexer::O_BRACE ) {
            cond = new LoopCondition(lex, table);
        }
        block = new Block(lex, table);
    }

    Loop::~Loop() {
        delete cond;
        delete block;
    }

    void Loop::Validate() const {
        cond->Validate();
        block->Validate();
    }

    void Loop::GenerateCode(std::ostream & out) const {
        
    }

    std::ostream& Loop::Write(std::ostream & os) const { 
        return os << "for " << *cond << *block;
    }

}