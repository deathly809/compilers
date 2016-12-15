
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
    };

    Operator::Operator(OperatorType type) : from(1), op(type) {
        /* Empty */
    }

    Operator::Operator(const Operator & other) : from(2), op(other.op) {
        /* Empty */
    }

    Operator::Operator(const Operator && other) : from(3), op(other.op) {
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

    std::ostream& operator<<(std::ostream& os,const Operator & op) {
        return os << op.ToString();
    }

}
