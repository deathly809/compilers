
#include <ast/Block.hpp>

#include <ast/Statements/Statement.hpp>
#include <ast/Statements/VariableDeclaration.hpp>
#include <ast/Statements/Assignment.hpp>
#include <ast/Statements/Return.hpp>
#include <ast/Statements/IfStatement.hpp>
#include <ast/Statements/Loop.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    Block::Block(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        consumeLexemeType(lex.Next(),lexer::O_BRACE);
        lex.HasNext();

        while(NextType(lex) != lexer::C_BRACE) {
            switch(NextType(lex)) {
                case lexer::VAR:
                case lexer::CONST:
                    stmts.push_back(new VariableDeclaration(lex,table));
                    break;
                case lexer::ID:
                    stmts.push_back(new Assignment(lex,table));
                case lexer::RETURN:
                    stmts.push_back(new Return(lex,table));
                    break;
                case lexer::IF:
                    stmts.push_back(new IfStatement(lex,table));
                    break;
                case lexer::LOOP:
                    stmts.push_back(new Loop(lex,table));
                    break;
                default:
                    throw std::runtime_error("error: " + std::to_string(__LINE__) + std::string(__FILE__));
            }
        }
        consumeLexemeType(lex.Next(),lexer::C_BRACE);
    }

    Block::~Block() {
        for( auto && s : stmts ) {
            delete s;
        }
        stmts.clear();
    }

    void Block::Block::Validate() const {
        for(auto && s : stmts) {
            s->Validate();
        }
    }

    void Block::GenerateCode(std::ostream & out) const {

    }

    std::ostream& Block::Write(std::ostream & os) const {
        os << "{" << std::endl; 
        for(auto && s : stmts) {
            os << *s << std::endl;
        }
        return os << std::endl << "}";
    }

}