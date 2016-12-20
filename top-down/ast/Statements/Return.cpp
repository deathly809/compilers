
#include <ast/Statements/Return.hpp>

#include <ast/Expressions/Expression.hpp>

#include <lexer/Lexer.hpp>
#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {
    Return::Return(lexer::Lexer& lex, symtable::SymbolTable * table) : Statement(table) {
        consumeLexemeType(lex,lexer::RETURN)
        if(NextType(lex) != lexer::C_BRACE && NextType(lex) != lexer::ENDFILE) {
            result = new Expression(lex,table);
        }
    }

    Return::~Return() {
        delete result;
    }

    void Return::Validate() const {
        if( result != nullptr) {
            result->Validate();
        }
    }

    std::unique_ptr<hardware::Register> Return::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        return nullptr;
    }

    std::ostream& Return::Write(std::ostream & os) const {
        os << "return";
        if(result != nullptr) {
            os << " " << *result;
        }
        return os;
    }

}