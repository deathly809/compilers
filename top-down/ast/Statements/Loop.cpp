
#include <ast/Statements/Loop.hpp>

#include <ast/Statements/LoopCondition.hpp>
#include <ast/Block.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    Loop::Loop(lexer::Lexer& lex, symtable::SymbolTable * table) : Statement(table) {
        consumeLexemeType(lex, lexer::LOOP);
        
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

    std::unique_ptr<hardware::Register> Loop::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        return nullptr;
    }

    std::ostream& Loop::Write(std::ostream & os) const { 
        return os << "for " << *cond << *block;
    }

}