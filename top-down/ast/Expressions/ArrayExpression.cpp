
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
        int scp = name->ScopeID();
        int idx = name->ScopePosition();
        if(idx != -1) {
            index->GenerateCode(codeGen);
            codeGen.LdA(scp,idx+1);
            codeGen.Add();
            codeGen.Ind();
        } else {
            throw std::runtime_error("unknown variable " + name->GetName());
        }
        return nullptr;
}

    std::ostream& ArrayExpression::Write(std::ostream & os) const {
        return os << *name << "[" << *index << "]";
    }

    ValueType ArrayExpression::ResultType() const {
        return name->ResultType();
    }

}

