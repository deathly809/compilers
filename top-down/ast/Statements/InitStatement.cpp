
#include <ast/Statements/InitStatement.hpp>
#include <ast/Statements/VariableDeclaration.hpp>
#include <ast/Statements/Assignment.hpp>

#include <symtable/SymbolTable.hpp>

#include <Lexer.hpp>
#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

#include <memory>

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
    void InitStatement::GenerateCode(std::ostream & os) const {

    }

    std::ostream& InitStatement::Write(std::ostream & os) const {
        if(assign != nullptr) {
            return assign->Write(os);
        } else {
            return varDef->Write(os);
        }
    }

}
