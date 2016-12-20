

#include <ast/Expressions/Literals/CharLiteral.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    CharLiteral::CharLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();
        
        value = Convert<char>(l->GetValue());
        
    }

    void CharLiteral::Validate() const {
        /* Empty */
    }

    std::unique_ptr<hardware::Register> CharLiteral::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        return nullptr;
    }

    ValueType CharLiteral::ResultType() const {
        return CharType;
    }

    char  CharLiteral::GetValue() const {
        return value;
    }

    std::ostream& CharLiteral::Write(std::ostream & os) const {
        return os << GetValue();
    }
}
