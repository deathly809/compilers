
#include <ast/ConstantBlock.hpp>

#include <ast/Statements/Assignment.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    ConstantBlock::ConstantBlock(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        
        consumeLexemeType(lex,lexer::CONST);
        consumeLexemeType(lex,lexer::O_PAREN);

        while(NextType(lex) != lexer::C_PAREN) {
            vars.push_back(new Assignment(lex, table));
        }
        consumeLexemeType(lex,lexer::C_PAREN);
    }

    ConstantBlock::~ConstantBlock() {
        for( auto&& v : vars ) {
            delete v;
        }
        vars.clear();
    }

    void ConstantBlock::Validate() const {
        for( auto&& v : vars ) {
            v->Validate();
        }
    }

    void ConstantBlock::GenerateCode(std::ostream & out) const {
    }

    std::ostream& ConstantBlock::Write(std::ostream & os) const {
        os << "const (" << std::endl;
        for(const auto & v : vars) {
            os << *v << std::endl;
        }
        return os << ")";
    }

}