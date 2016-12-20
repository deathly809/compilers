
#include <ast/Expressions/ArrayExpression.hpp>

#include <ast/Identifier.hpp>
#include <ast/Expressions/Expression.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    ArrayExpression::ArrayExpression(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        name = new Identifier(lex, table);
        consumeLexemeType(lex,lexer::O_BRACKET);
        index = new Expression(lex, table);
        consumeLexemeType(lex,lexer::C_BRACKET);
    }

    void ArrayExpression::Validate() const {
        name->Validate();
        index->Validate();
    }

    std::unique_ptr<hardware::Register> ArrayExpression::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        // REG_OUT = REG_NAME[REG_IDX]
        return nullptr;
}

    std::ostream& ArrayExpression::Write(std::ostream & os) const {
        return os << *name << "[" << *index << "]";
    }

    ValueType ArrayExpression::ResultType() const {
        return NilType;
    }

}

