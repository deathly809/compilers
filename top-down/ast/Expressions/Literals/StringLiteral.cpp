
#include <ast/Expressions/Literals/StringLiteral.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    StringLiteral::StringLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();
        
        value = l->GetValue();
    }

    void StringLiteral::Validate() const {
        /* Empty */
    }

    std::unique_ptr<hardware::Register> StringLiteral::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        return nullptr;
    }

    ValueType StringLiteral::ResultType() const {
        return StringType;
    }

    std::string StringLiteral::GetValue() const {
        return value;
    }

    std::ostream& StringLiteral::Write(std::ostream & os) const {
        return os << "\"" << GetValue() << "\"";
    }

}
