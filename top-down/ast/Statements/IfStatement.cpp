
#include <ast/Statements/IfStatement.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Block.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    IfStatement::IfStatement(lexer::Lexer & lex, symtable::SymbolTable * table) : Statement(table) {
        consumeLexemeType(lex, lexer::IF);

        cond = new Expression(lex, table);
        trueBlock = new Block(lex, table);
        if(NextType(lex) == lexer::ELSE) {
            consumeLexemeType(lex, lexer::ELSE);
            falseBlock = new Block(lex, table);
        }
    }

    IfStatement::~IfStatement() {
        delete cond;
        delete trueBlock;
        delete falseBlock;
    }

    void IfStatement::Validate() const {
        cond->Validate();
        trueBlock->Validate();
        if(falseBlock != nullptr) {
            falseBlock->Validate();
        }
    }

    std::unique_ptr<hardware::Register> IfStatement::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        return nullptr;
    }

    std::ostream& IfStatement::Write(std::ostream & os) const {
        os << "if " << *cond << " " << *trueBlock;
        if(falseBlock != nullptr) {
            os << " else " << *falseBlock;
        }
        return os;
    }

}