
#include <ast/Expressions/Factor.hpp>

#include <ast/Expressions/Term.hpp>
#include <ast/Expressions/Operator.hpp>

#include <ast/Expressions/InvalidTypeCombination.hpp>

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
            IntType, 
            {
                Operator::MultiplicationOperator,
                Operator::DivisionOperator, 
                Operator::ModulusOperator
            }
        },
        {
            RealType, 
            {
                Operator::MultiplicationOperator,
                Operator::DivisionOperator
            }
        },
        {
            BoolType,
            {
                Operator::AndOperator
            }
        }
    };

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
        if(rhs != nullptr) {

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
                throw std::runtime_error("expressions must return a non-nil value:" + std::to_string(__LINE__) + " " + std::string(__FILE__));
            }
        }
    }

    std::unique_ptr<hardware::Register> Factor::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        lhs->GenerateCode(codeGen);
        if(rhs != nullptr) {
            rhs->GenerateCode(codeGen);
            op->GenerateCode(codeGen);
        }
        return nullptr;
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
