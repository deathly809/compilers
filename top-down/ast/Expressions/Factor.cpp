
#include <ast/Expressions/Factor.hpp>

#include <ast/Expressions/Term.hpp>
#include <ast/Expressions/Operator.hpp>

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
    Factor::Factor(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) { //, lhs(nullptr), rhs(nullptr), op(nullptr) {
        rhs = new Term(lex, table);        
        
        bool doIt = true;

        Operator* op;

        while(doIt) {
            switch(NextType(lex)) {
                case lexer::MUL:
                    op = new Operator(Operator::MultiplicationOperator);
                    list.push_back({rhs,op});
                    lex.Next();
                    lex.HasNext();
                    rhs = new Term(lex, table);
                    break;
                case lexer::DIV:
                    op = new Operator(Operator::DivisionOperator);
                    list.push_back({rhs,op});
                    lex.Next();
                    lex.HasNext();
                    rhs = new Term(lex, table);
                    break;
                case lexer::AND:
                    op = new Operator(Operator::AndOperator);
                    list.push_back({rhs,op});
                    lex.Next();
                    lex.HasNext();
                    rhs = new Term(lex, table);
                    break;
                case lexer::MOD:
                    op = new Operator(Operator::ModulusOperator);
                    list.push_back({rhs,op});
                    lex.Next();
                    lex.HasNext();
                    rhs = new Term(lex, table);
                    break;
                default:
                    doIt = false;
                    //op = new Operator(Operator::None);
                    break;
            }
        }

        /*
        // We found an operator, consume it
        if(op->GetType() != Operator::None) {
            lex.Next();
            lex.HasNext();
            rhs = new Factor(lex,table);
        }
        */
    }

    Factor::~Factor() {
        for(auto & p : list) {
            delete p.lhs;
            delete p.op;
        }
        list.clear();
        //delete lhs;
        //delete op;
        delete rhs;
    }

    void Factor::Validate() const {
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

    std::unique_ptr<hardware::Register> Factor::GenerateCode(hardware::InstructionGenerator & codeGen) const {
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

    ValueType Factor::ResultType() const {
        return rhs->ResultType();
    }

    std::ostream& Factor::Write(std::ostream & os) const {
        for(auto & p : list) {
            os << *p.lhs << " " <<  *p.op << " ";
        }
        return os << *rhs;
    }
}
