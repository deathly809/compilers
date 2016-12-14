
#include <ast/Expressions/Expression.hpp>

#include <ast/Expressions/InvalidTypeCombination.hpp>
#include <ast/Expressions/Operator.hpp>
#include <ast/Expressions/Factor.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    // E := F | F ( "+" | "-" | "|" ) E
    // F := T | T ( "*" | "/" | "%" | "&" ) F
    // T := (E) | ID | LIT | F_CALL
    Expression::Expression(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), lhs(nullptr), rhs(nullptr), op(nullptr) {
        
        lhs = new Factor(lex, table);
        lexer::Lexeme *l = lex.Next();
        lex.HasNext();

        switch(l->GetType()) {
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
                lex.PushBack(l);
                break;
        }

        if(op->GetType() != Operator::None) {
            delete l;
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

    void Expression::Validate() {
        if(rhs != nullptr) {
            if(lhs->ResultType() != rhs->ResultType()) {
                throw std::runtime_error("mismatched types: " + std::to_string(__LINE__) + " " + std::string(__FILE__));
            }
            switch(lhs->ResultType()) {
                case StringType:
                    if(op->GetType() != Operator::AdditionOperator) {
                        throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
                    }
                    break;
                case RealType:
                    if(op->GetType() == Operator::ModulusOperator) {
                        throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
                    }
                    break;
                case BoolType:
                    if(op->GetType() != Operator::OrOperator) {
                        throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
                    }
                    break;
                case NilType:
                        throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
                        break;
                default:
                    throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
            }
        }
    }

    void Expression::GenerateCode(std::ostream & out) {
        // TODO : Generate the code!
    }

    ValueType Expression::ResultType() {
        return lhs->ResultType();
    } 

}
