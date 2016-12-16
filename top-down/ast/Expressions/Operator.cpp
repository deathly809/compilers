
#include <ast/Expressions/Operator.hpp>

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

    void Operator::GenerateCode(std::ostream & os) const {
        /* empty */
    }

    std::ostream& Operator::Write(std::ostream& os) const {
        return os << ToString();
    }

}