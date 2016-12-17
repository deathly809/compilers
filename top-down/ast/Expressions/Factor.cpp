
#include <ast/Expressions/Factor.hpp>

#include <ast/Expressions/Term.hpp>
#include <ast/Expressions/Operator.hpp>

#include <ast/Expressions/InvalidTypeCombination.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

namespace ast {

    // E = F | F ( "+" | "-" | "|" ) E
    // F = T | T ( "*" | "/" | "%" | "&" ) F
    // T = (E) | ID | LIT | F_CALL
    Factor::Factor(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), lhs(nullptr), rhs(nullptr), op(nullptr) {
        lhs = new Term(lex, table);        
        
        switch(NextType(lex)) {
            case lexer::MUL:
                op = new Operator(Operator::MultiplicationOperator);
                break;
            case lexer::DIV:
                op = new Operator(Operator::DivisionOperator);
                break;
            case lexer::AND:
                op = new Operator(Operator::AndOperator);
                break;
            case lexer::MOD:
                op = new Operator(Operator::ModulusOperator);
                break;
            default:
                op = new Operator(Operator::None);
                break;
        }

        // We found an operator, consume it
        if(op->GetType() != Operator::None) {
            lex.Next();
            lex.HasNext();
            rhs = new Factor(lex,table);
        }

    }

    Factor::~Factor() {
        delete lhs;
        delete op;
        delete rhs;
    }

    void Factor::Validate() const {
        
        ValueType type = lhs->ResultType();
        if( type == NilType) {
            throw std::runtime_error("expressions must return a non-nil value:" + std::to_string(__LINE__) + " " + std::string(__FILE__));
        }

        if(rhs != nullptr) {

            if(lhs->ResultType() != rhs->ResultType()) {
                throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
            }

            // Supported operations:
            //
            //  Division: REAL, INT
            //  Multiplication: Real Int
            //  Modulus: Int
            //  Or: Bool
            //  And: Bool
            switch(op->GetType()) {
                case Operator::MultiplicationOperator:
                case Operator::DivisionOperator:
                    if(type != RealType && type != IntType) {
                        throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
                    }
                    break;
                case Operator::ModulusOperator:
                    if(type != IntType) {
                        throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);    
                    }
                    break;
                case Operator::AndOperator:
                case Operator::OrOperator:
                    if(type != BoolType) {
                        throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);  
                    }
                    break;
                default:
                    throw std::runtime_error("Invalid operator: " + std::to_string(__LINE__) + " " + std::string(__FILE__));
                    break;
            }
        }
    }

    void Factor::GenerateCode(std::ostream & out) const {
        // TODO : Generate the code!
    }

    ValueType Factor::ResultType() const {
        return lhs->ResultType();
    }

    std::ostream& Factor::Write(std::ostream & os) const {
        if(op->GetType() == Operator::None) {
            os << *lhs;
        } else {
            os << "(" << *lhs <<  *op << *rhs << ")";
        }
        return os;
    }
}
