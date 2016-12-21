
#include <ast/Expressions/Term.hpp>

#include <ast/Expressions/VName.hpp>
#include <ast/Expressions/Operator.hpp>
#include <ast/Expressions/InvalidTypeCombination.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {



    // T = (E) | ID | LIT | F_CALL
    Term::Term(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table), lhs(nullptr), op(nullptr), rhs(nullptr) {
        lhs = new VName(lex,table);

        switch(NextType(lex)) {
            case lexer::LT:
                op = new Operator(Operator::LessThan);
                break;
            case lexer::LTE:
                op = new Operator(Operator::LessThanOrEqual);
                break;
            case lexer::GT:
                op = new Operator(Operator::GreaterThan);
                break;
            case lexer::GTE:
                op = new Operator(Operator::GreaterThanOrEqual);
                break;
            case lexer::NE:
                op = new Operator(Operator::NotEqual);
                break;
            case lexer::D_EQUAL:
                op = new Operator(Operator::EqualTo);
                break;
            default:
                op = new Operator(Operator::None);
                break;
        }

        if(op->GetType() != Operator::None) {
            lex.Next();
            lex.HasNext();
            rhs = new Term(lex, table);
        }
    }

    Term::~Term() {
        delete lhs;
        delete op;
        delete rhs;
    }

    void Term::Validate() const {
        lhs->Validate();
        if(rhs != nullptr) {
            rhs->Validate();

            if(lhs->ResultType() != rhs->ResultType()) {
                throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
            }

            if(lhs->ResultType() != ValueType::IntType) {
                throw InvalidTypeCombination(lhs->ResultType(),rhs->ResultType(),op,__LINE__,__FILE__);
            }
        }
    }

    std::unique_ptr<hardware::Register> Term::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        lhs->GenerateCode(codeGen);
        if(rhs != nullptr) {
            rhs->GenerateCode(codeGen);
            op->GenerateCode(codeGen);
        }
        return nullptr;
    }

    ValueType Term::ResultType() const {
        return lhs->ResultType();
    }

    std::ostream & Term::Write(std::ostream & os) const {
        if(op->GetType() == Operator::None) {
            os << *lhs;
        } else {
            os << "(" << *lhs << *op << *rhs << ")";
        }
        return os;
    }

}
