

#include <ast/Expressions/Literals/IntegerLiteral.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    IntegerLiteral::IntegerLiteral(int value) : Ast(nullptr), value(value) {
        /* Empty */
    }

    IntegerLiteral::IntegerLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();
        
        value = Convert<int>(l->GetValue());
        
    }

    void IntegerLiteral::Validate() const {
        /* Empty */
    }

    std::unique_ptr<hardware::Register> IntegerLiteral::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        codeGen.LdC(value);
        return nullptr;
    }

    ValueType IntegerLiteral::ResultType() const {
        return IntType;
    }

    int  IntegerLiteral::GetValue() const {
        return value;
    }

    std::ostream& IntegerLiteral::Write(std::ostream & os) const {
        return os << GetValue();
    }
}
