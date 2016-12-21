
#include <ast/Expressions/Operator.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <string>

#include <iostream>

#include <map>

namespace ast {


    static std::map<Operator::OperatorType,std::string> mappings = {
        {Operator::AdditionOperator, "+"},
        {Operator::SubtractionOperator, "-"},
        {Operator::MultiplicationOperator, "*"},
        {Operator::DivisionOperator, "/"},
        {Operator::ModulusOperator, "%"},
        {Operator::OrOperator, "|"},
        {Operator::AndOperator, "&"},
        {Operator::LessThan, "<"},
        {Operator::LessThanOrEqual, "<="},
        {Operator::GreaterThan, ">"},
        {Operator::GreaterThanOrEqual, ">="},
        {Operator::EqualTo, "=="},
        {Operator::NotEqual, "!="},
    };

    Operator::Operator(OperatorType type) : Ast(nullptr), op(type) {
        /* Empty */
    }

    Operator::Operator(const Operator & other) : Ast(nullptr), op(other.op) {
        /* Empty */
    }

    Operator::Operator(const Operator && other) : Ast(nullptr), op(other.op) {
        /* Empty */
    }

    Operator::OperatorType Operator::GetType() const {
        return op;
    }

    std::string Operator::ToString() const {
        auto && ptr = mappings.find(op);
        if(ptr == mappings.end()) {
            throw std::runtime_error("compiler is broken: " + std::to_string(op) + " - " + std::to_string(__LINE__) + " " + std::string(__FILE__));
        }
        return ptr->second;
    }

    void Operator::Validate() const {
        /* empty */
    }

    std::unique_ptr<hardware::Register> Operator::GenerateCode(hardware::InstructionGenerator & gen) const {
        switch(op) {
            case Operator::AdditionOperator:
                gen.Add();
                break;
            case Operator::SubtractionOperator:
                gen.Sub();
                break;
            case Operator::MultiplicationOperator:
                gen.Mult();
                break;
            case Operator::DivisionOperator:
                gen.Div();
                break;
            case Operator::ModulusOperator:
                gen.Mod();
                break;
            case Operator::OrOperator:
                gen.Or();
                break;
            case Operator::AndOperator:
                gen.And();
                break;
            case Operator::LessThan:
                gen.Lt();
                break;
            case Operator::LessThanOrEqual:
                gen.Le();
                break;
            case Operator::GreaterThan:
                gen.Gt();
                break;
            case Operator::GreaterThanOrEqual:
                gen.Ge();
                break;
            case Operator::EqualTo:
                gen.Eq();
                break;
            case Operator::NotEqual:
                gen.Ne();
                break;
            default:
                break;
        }
        return nullptr;
    }

    std::ostream& Operator::Write(std::ostream& os) const {
        return os << ToString();
    }

}
