
#ifndef INVALIDTYPECOMBINATION_HPP_
#define INVALIDTYPECOMBINATION_HPP_

#include <exception>
#include <stdexcept>
#include <sstream>

#include <ast/Type.hpp>
#include <ast/Expressions/Operator.hpp>

namespace ast {

    class InvalidTypeCombination : public std::runtime_error {

        public:
            InvalidTypeCombination(ValueType lhs, ValueType rhs, Operator* bop, int line, const char* file) : std::runtime_error("invalid type operator combination"), line(line), file(std::string(file)), lhs(lhs), rhs(rhs), bop(bop) {
                /* Empty */
            }

            virtual const char* what() const throw() {
                std::ostringstream cnvt( "" );
                cnvt << runtime_error::what() << ": " << file << "(" << line << ") " << GetTypeLeft() << " " << GetOperator() << " " << GetTypeRight(); 
                return cnvt.str().c_str();
            }

        private:
            std::string GetTypeLeft() const {
                return ValueTypeToString(lhs);
            }

            std::string GetTypeRight() const {
                return ValueTypeToString(rhs);
            }

            std::string GetOperator() const {
                return bop->ToString();
            }

        private:
            const int line;
            const std::string file;
            const ValueType lhs, rhs;
            const Operator* bop;

    };

}

#endif