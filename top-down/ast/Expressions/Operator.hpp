
#ifndef OPERATOR_HPP_
#define OPERATOR_HPP_

#include <string>

namespace ast {

    class Operator {

        public:

            enum OperatorType {
                AdditionOperator, SubtractionOperator, OrOperator,
                MultiplicationOperator , DivisionOperator , ModulusOperator,
                AndOperator , None  
            };

            Operator(OperatorType type);
            Operator(const Operator & other);
            Operator(const Operator && other);

            OperatorType GetType() const;
            std::string ToString() const;

        private:
            Operator() = delete;
            int from = -1;
            Operator::OperatorType op = Operator::None;

            friend std::ostream& operator<<(std::ostream& os,const Operator & op);

    };

    std::ostream& operator<<(std::ostream& os,const Operator & op);
}

#endif