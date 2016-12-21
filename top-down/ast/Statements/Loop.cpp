
#include <ast/Statements/Loop.hpp>

#include <ast/Statements/InitStatement.hpp>
#include <ast/Statements/Assignment.hpp>
#include <ast/Expressions/Expression.hpp>

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


    //      INIT
    //TOP:  COND
    //      JMPF BOTTOM
    //      BODY
    //      UPDATE
    //      goto TOP
    //BOTTOM:
    //
    //
    std::unique_ptr<hardware::Register> Loop::GenerateCode(hardware::InstructionGenerator & codeGen) const {

        std::string top = codeGen.GenerateLabel();

        if(cond != nullptr) {

            auto init = cond->GetInit();
            auto test = cond->GetCondition();
            auto incr = cond->GetUpdate();

            std::string bottom = codeGen.GenerateLabel();

            if(init != nullptr) init->GenerateCode(codeGen);
            codeGen.WriteLabel(top);

            test->GenerateCode(codeGen);
            codeGen.JmpF(bottom);

            block->GenerateCode(codeGen);

            if(incr != nullptr) incr->GenerateCode(codeGen);

            codeGen.Jmp(top);

            codeGen.WriteLabel(bottom);
        } else {
            codeGen.WriteLabel(top);
            block->GenerateCode(codeGen);
            codeGen.Jmp(top);
        }

        return nullptr;
    }

    std::ostream& Loop::Write(std::ostream & os) const { 
        return os << "for " << *cond << *block;
    }

}