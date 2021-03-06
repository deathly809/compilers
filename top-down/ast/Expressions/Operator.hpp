
#ifndef OPERATOR_HPP_
#define OPERATOR_HPP_

#include <ast/Ast.hpp>

#include <string>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Operator : public Ast {

        public:

            enum OperatorType {
                AdditionOperator, SubtractionOperator, OrOperator,
                MultiplicationOperator , DivisionOperator , ModulusOperator, AndOperator,
                LessThan, LessThanOrEqual, GreaterThan, GreaterThanOrEqual, EqualTo, NotEqual,
                NotOperator, NegationOperator, PositiveOperator,
                None,  
            };

            Operator(OperatorType type);
            Operator(const Operator & other);
            Operator(const Operator && other);

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & gen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            OperatorType GetType() const;
            std::string ToString() const;

        private:
            Operator() = delete;
            Operator::OperatorType op = Operator::None;

    };
}

#endif