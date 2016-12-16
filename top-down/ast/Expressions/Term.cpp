
#include <ast/Expressions/Term.hpp>

#include <ast/Expressions/VName.hpp>
#include <ast/Expressions/Operator.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    // T := (E) | ID | LIT | F_CALL
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
    }

    void Term::GenerateCode(std::ostream & out) const {
        // TODO : Generate the code!
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
