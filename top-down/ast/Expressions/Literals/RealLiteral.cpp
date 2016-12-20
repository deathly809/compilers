
#include <ast/Expressions/Literals/RealLiteral.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    RealLiteral::RealLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();

        value = Convert<double>(l->GetValue());
    }

    void RealLiteral::Validate() const {
        /* Empty */
    }

    std::unique_ptr<hardware::Register> RealLiteral::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        return nullptr;
    }

    ValueType RealLiteral::ResultType() const {
        return RealType;
    }

    double  RealLiteral::GetValue() const {
        return value;
    }

    std::ostream& RealLiteral::Write(std::ostream & os) const {
        return os << GetValue();
    }
    

}
