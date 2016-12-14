
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

            Operator(OperatorType type) : op(type) {
                /* Empty */
            }

            Operator(const Operator & other) : op(other.op) {
                /* Empty */
            }

            OperatorType GetType() const {
                return op;
            }

            std::string ToString() const {
                
                switch(op) {
                    case AdditionOperator:
                        return "+";
                    case SubtractionOperator:
                        return "-";
                    case OrOperator:
                        return "|";
                    case MultiplicationOperator:
                        return "*";
                    case DivisionOperator:
                        return "/";
                    case ModulusOperator:
                        return "%";
                    case AndOperator:
                        return "&";
                    case None:
                        return "NIL";
                    default:
                        std::cout << op << std::endl;
                }

                throw std::runtime_error("compiler is broken: " + std::to_string(__LINE__) + " " + std::string(__FILE__));
            }

        private:
            OperatorType op = None;

    };

}

#endif