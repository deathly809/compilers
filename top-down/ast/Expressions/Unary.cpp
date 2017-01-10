
#include <ast/Expressions/Unary.hpp>

#include <ast/Expressions/VName.hpp>
#include <ast/Expressions/Operator.hpp>
#include <ast/Expressions/InvalidTypeCombination.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {



    // T = (E) | ID | LIT | F_CALL
    Unary::Unary(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), op(nullptr) {

        switch(NextType(lex)) {
            case lexer::BANG:
                op = new Operator(Operator::NotOperator);
                break;
            case lexer::MINUS:
                op = new Operator(Operator::NegationOperator);
                break;
            case lexer::PLUS:
                op = new Operator(Operator::PositiveOperator);
                break;
            default:
                op = nullptr;
                break;
        }

        if(op != nullptr) {
            lex.Next();
            lex.HasNext();
            value.unary = new Unary(lex, table);
        }else {
            value.vname = new VName(lex, table);
        }
    }

    Unary::~Unary() {
        if(op != nullptr) {
            delete op;
            delete value.unary;
        } else {
            delete value.vname;
        }
    }

    void Unary::Validate() const {
        if(op!= nullptr) {
            value.unary->Validate();
        } else {
            value.vname->Validate();
        }
    }

    std::unique_ptr<hardware::Register> Unary::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        if(op != nullptr) {
            value.unary->GenerateCode(codeGen);
            op->GenerateCode(codeGen);
        } else {
            value.vname->GenerateCode(codeGen);
        }
        return nullptr;
    }

    ValueType Unary::ResultType() const {
        ValueType type = NilType;
        if(op != nullptr) {
            type = value.unary->ResultType();
            switch(op->GetType()) {
                case Operator::NotOperator:
                    if(type != BoolType) {
                        throw std::runtime_error("unary ! expects a boolean type\n");
                    }
                    break;
                case Operator::PositiveOperator:
                    if(type != IntType) {
                        throw std::runtime_error("unary + expects a boolean type\n");
                    }
                    break;
                case Operator::NegationOperator:
                    if(type != IntType) {
                        throw std::runtime_error("unary - expects a boolean type\n");
                    }
                    break;
                default:
                    throw std::runtime_error("Unary: invalid type");
                    break;
            }
        } else {
            type = value.vname->ResultType();
        }
        return type;
    }

    std::ostream & Unary::Write(std::ostream & os) const {
        if(op != nullptr) {
            op->Write(os);
            return os << *value.unary;
        } else {
            return os << *value.vname;
        }
    }

}
