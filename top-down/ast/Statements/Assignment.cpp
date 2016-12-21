#include <ast/Statements/Assignment.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    Assignment::Assignment(lexer::Lexer & lex, symtable::SymbolTable* table) : Statement(table) {
        lhs = new Identifier(lex, table);
        if(NextType(lex) == lexer::O_BRACKET) {
            consumeLexemeType(lex,lexer::O_BRACKET);
            index = new Expression(lex, table);
            consumeLexemeType(lex,lexer::C_BRACKET);
        }
        consumeLexemeType(lex,lexer::EQUAL);
        rhs = new Expression(lex, table);
    }

    Assignment::~Assignment() {
        delete lhs;
        delete index;
        delete rhs;
    }

    void Assignment::Validate() const {
        lhs->Validate();
        if(index != nullptr) index->Validate();
        rhs->Validate();
    }

    std::unique_ptr<hardware::Register> Assignment::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        rhs->GenerateCode(codeGen);
        int scope = lhs->ScopeID();
        int pos = lhs->ScopePosition();
        codeGen.St(
                scope,
                pos + 1
            );
        return nullptr;
    }

    std::ostream& Assignment::Write(std::ostream & os) const {
        if(index != nullptr) {
            return os << *lhs << "[" << *index << "] = " << *rhs;
        } else {
            return os << *lhs << " = " << *rhs;
        }
    }

}