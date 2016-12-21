
#include <ast/Expressions/Expression.hpp>

#include <ast/Expressions/Operator.hpp>
#include <ast/Expressions/Factor.hpp>

#include <ast/Expressions/InvalidTypeCombination.hpp>
#include <ast/Expressions/NilExpression.hpp>


#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <map>
#include <vector>
#include <algorithm>

namespace ast {


    static std::map<ValueType,std::vector<Operator::OperatorType>> acceptableTables = 
    {
        {
            CharType,
            {
                Operator::AdditionOperator,
                Operator::SubtractionOperator
            }
        },
        {
            IntType, 
            {
                Operator::AdditionOperator,
                Operator::SubtractionOperator
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
        lhs->Validate();
        if(rhs != nullptr) {
            rhs->Validate();

            if(lhs->ResultType() != rhs->ResultType()) {
                throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);                
            }

            const auto & options = acceptableTables.find(lhs->ResultType());
            if( options == acceptableTables.end()) {
                throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);                
            }

            const auto & ptr = std::find(options->second.begin(), options->second.end(), op->GetType()); 
            if(ptr == options->second.end()) {
                throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
            }

        } else {
            ValueType type = lhs->ResultType();
            if( type == NilType) {
                throw NilExpression(__FILE__, __LINE__);
            }
        }
    }

    std::unique_ptr<hardware::Register> Expression::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        lhs->GenerateCode(codeGen);
        if(rhs != nullptr) {
            rhs->GenerateCode(codeGen);
            op->GenerateCode(codeGen);
        }
    return nullptr;
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
