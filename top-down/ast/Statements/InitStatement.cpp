
#include <ast/Statements/InitStatement.hpp>
#include <ast/Statements/VariableDeclaration.hpp>
#include <ast/Statements/Assignment.hpp>

#include <symtable/SymbolTable.hpp>

#include <lexer/Lexer.hpp>
#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

        
    InitStatement::InitStatement(lexer::Lexer& lex, symtable::SymbolTable * sym) : Ast(sym), varDef(nullptr), assign(nullptr) {
        if(NextType(lex) == lexer::VAR) {
            varDef = new VariableDeclaration(lex,sym);
        }else {
            assign = new Assignment(lex,sym);
        }
    }

    InitStatement::~InitStatement() {
        delete varDef;
        delete assign;
    }

    void InitStatement::Validate() const {
        if(assign != nullptr) {
            assign->Validate();
        } else {
            varDef->Validate();
        }
    }
    std::unique_ptr<hardware::Register> InitStatement::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        if(assign != nullptr) {
            return assign->GenerateCode(codeGen);
        } else {
            return varDef->GenerateCode(codeGen);
        }
    }

    std::ostream& InitStatement::Write(std::ostream & os) const {
        if(assign != nullptr) {
            return assign->Write(os);
        } else {
            return varDef->Write(os);
        }
    }

}
