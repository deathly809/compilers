
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
    Expression::Expression(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) { //, lhs(nullptr), rhs(nullptr), op(nullptr) {
        
        rhs = new Factor(lex, table);
        Operator *op;

        bool doIt = true;
        while(doIt) {
            switch(NextType(lex)) {
                case lexer::PLUS:
                    op = new Operator(Operator::AdditionOperator);
                    lex.Next();
                    lex.HasNext();
                    list.push_back({rhs,op});
                    rhs = new Factor(lex ,table);
                    break;
                case lexer::MINUS:
                    op = new Operator(Operator::SubtractionOperator);
                    lex.Next();
                    lex.HasNext();
                    list.push_back({rhs,op});
                    rhs = new Factor(lex ,table);
                    break;
                case lexer::OR:
                    op = new Operator(Operator::OrOperator);
                    lex.Next();
                    lex.HasNext();
                    list.push_back({rhs,op});
                    rhs = new Factor(lex ,table);
                    break;
                default:
                    // op = new Operator(Operator::None);
                    doIt = false;
                    break;
            }
        }

        /*
        if(op->GetType() != Operator::None) {
            lex.Next();
            lex.HasNext();
            rhs = new Expression(lex,table);
        } else {
            // pushed l back
        }
        */
    }

    Expression::~Expression() {
        for(auto & p : list) {
            delete p.lhs;
            delete p.op;
        }
        list.clear();
        //delete lhs;
        //delete op;
        delete rhs;
    }

    void Expression::Validate() const {
        rhs->Validate();
        if( rhs->ResultType() == NilType) {
            throw NilExpression(__FILE__, __LINE__);
        }

        for(auto & p : list) {
            auto lhs = p.lhs;
            auto op  = p.op;
            
            lhs->Validate();

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

        }

    }

    std::unique_ptr<hardware::Register> Expression::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        if(list.size() > 0) {
            list[0].lhs->GenerateCode(codeGen);
            for(size_t i = 1; i < list.size();i++) {
                list[i].lhs->GenerateCode(codeGen);
                list[i-1].op->GenerateCode(codeGen);
            }

            rhs->GenerateCode(codeGen);
            list[list.size()-1].op->GenerateCode(codeGen);
        } else {
            rhs->GenerateCode(codeGen);
        }
        return nullptr;
    }

    ValueType Expression::ResultType() const {
        return rhs->ResultType();
    } 

    std::ostream & Expression::Write(std::ostream & os) const {
        for(auto & p : list) {
            os << *p.lhs << " " <<  *p.op << " ";
        }
        return os << *rhs;
        /*
        if(op->GetType() == Operator::None) {
            os << *lhs;
        } else {
            os << "(" << *lhs << *op << *rhs << ")";
        }
        return os;
        */
    }

}
