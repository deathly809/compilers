
#include <ast/Expressions/Expression.hpp>

#include <ast/Expressions/InvalidTypeCombination.hpp>
#include <ast/Expressions/Operator.hpp>
#include <ast/Expressions/Factor.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <map>
#include <vector>

#include <algorithm>

namespace ast {


    std::map<ValueType,std::vector<Operator::OperatorType>> acceptableTables = 
    {
        {
            IntType, 
            {
                Operator::AdditionOperator,
                Operator::SubtractionOperator, 
                Operator::ModulusOperator
            }
        },
        {
            RealType, 
            {
                Operator::AdditionOperator,
                Operator::SubtractionOperator
            }
        },
        {
            StringType,
            {
                Operator::AdditionOperator
            }
        },
        {
            BoolType,
            {
                Operator::OrOperator
            }
        }
    };

    // E = F | F ( "+" | "-" | "|" ) E
    // F = T | T ( "*" | "/" | "%" | "&" ) F
    // T = (E) | ID | LIT | F_CALL
    Expression::Expression(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), lhs(nullptr), rhs(nullptr), op(nullptr) {
        
        lhs = new Factor(lex, table);

        switch(NextType(lex)) {
            case lexer::PLUS:
                op = new Operator(Operator::AdditionOperator);
                break;
            case lexer::MINUS:
                op = new Operator(Operator::SubtractionOperator);
                break;
            case lexer::OR:
                op = new Operator(Operator::OrOperator);
                break;
            default:
                op = new Operator(Operator::None);
                break;
        }

        if(op->GetType() != Operator::None) {
            lex.Next();
            lex.HasNext();
            rhs = new Expression(lex,table);
        } else {
            // pushed l back
        }
    }

    Expression::~Expression() {
        delete lhs;
        delete op;
        delete rhs;
    }

    void Expression::Validate() const {
        if(rhs != nullptr) {

            if(lhs->ResultType() != rhs->ResultType()) {
                throw std::runtime_error("mismatched types: " + std::to_string(__LINE__) + " " + std::string(__FILE__));
            }

            const auto & options = acceptableTables[lhs->ResultType()];
            const auto & ptr = std::find(options.begin(), options.end(), op->GetType()); 
            if(ptr == options.end()) {
                throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
            }

        }
    }

    void Expression::GenerateCode(std::ostream & out) const {
        // TODO : Generate the code!
    }

    ValueType Expression::ResultType() const {
        return lhs->ResultType();
    } 

    std::ostream & Expression::Write(std::ostream & os) const {
        if(op->GetType() == Operator::None) {
            os << *lhs;
        } else {
            os << "(" << *lhs << *op << *rhs << ")";
        }
        return os;
    }

}
