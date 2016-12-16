
#include <ast/Block.hpp>

#include <ast/Statements/Statement.hpp>
#include <ast/Statements/VariableDeclaration.hpp>
#include <ast/Statements/Assignment.hpp>
#include <ast/Expressions/FunctionCall.hpp>
#include <ast/Statements/Return.hpp>
#include <ast/Statements/IfStatement.hpp>
#include <ast/Statements/Loop.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <ast/UnexpectedToken.hpp>

namespace ast {

    Block::Block(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        std::unique_ptr<lexer::Lexeme> tmp = nullptr;

        consumeLexemeType(lex,lexer::O_BRACE);
        while(NextType(lex) != lexer::C_BRACE) {
            switch(NextType(lex)) {
                case lexer::VAR:
                case lexer::CONST:
                    stmts.push_back(new VariableDeclaration(lex,table));
                    break;
                case lexer::ID:
                    tmp = std::move(lex.Next());
                    lex.HasNext();
                    if(NextType(lex) == lexer::O_PAREN) {
                        lex.PushBack(tmp);
                        stmts.push_back(new FunctionCall(lex,table));
                    } else {
                        lex.PushBack(tmp);
                        stmts.push_back(new Assignment(lex,table));
                    }
                    break;
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
                    throw UnexpectedToken(lex.Next(),__FILE__,__LINE__);
            }
        }
        consumeLexemeType(lex,lexer::C_BRACE);
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
        if(stmts.size() == 0 ) {
            os << std::endl;
        }
        return os << "}";
    }

}