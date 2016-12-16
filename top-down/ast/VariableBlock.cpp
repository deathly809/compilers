
#include <ast/VariableBlock.hpp>

#include <ast/Statements/Assignment.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    VariableBlock::VariableBlock(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        
        consumeLexemeType(lex,lexer::VAR);
        consumeLexemeType(lex,lexer::O_PAREN);

        while(NextType(lex) != lexer::C_PAREN) {
            vars.push_back(new Assignment(lex, table));
        }
        consumeLexemeType(lex,lexer::C_PAREN);
    }

    VariableBlock::~VariableBlock() {
        for( auto&& v : vars ) {
            delete v;
        }
        vars.clear();
    }

    void VariableBlock::Validate() const {
        for( auto&& v : vars ) {
            v->Validate();
        }
    }

    void VariableBlock::GenerateCode(std::ostream & out) const {
    }

    std::ostream& VariableBlock::Write(std::ostream & os) const {
        os << "var (" << std::endl;
        for(const auto & v : vars) {
            os << *v << std::endl;
        }
        return os << ")";
    }

}