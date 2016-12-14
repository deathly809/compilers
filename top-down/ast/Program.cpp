
#include <ast/Program.hpp>

#include <ast/FunctionDefinition.hpp>
#include <ast/ConstantBlock.hpp>
#include <ast/VariableBlock.hpp>

#include <symtable/SymbolTable.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    Program::Program(lexer::Lexer & lex) : Ast(new symtable::SymbolTable()) {
        
        while(lex.HasNext()) {
            lexer::Lexeme* l = lex.Next();
            switch(l->GetType()) {
                case lexer::FUNC:
                    funcs.push_back(new FunctionDefinition(lex, table));
                    break;
                case lexer::CONST:
                    consts.push_back(new ConstantBlock(lex, table));
                    break;
                case lexer::VAR:
                    vars.push_back(new VariableBlock(lex, table));
                    break;
                default:
                    throw std::runtime_error("Unexpected token");
            }
        }
    }

    Program::~Program() {
        for( auto&& f : funcs ) {
            delete f;
        }
        for( auto&& c : consts ) {
            delete c;
        }
        for( auto&& v : vars ) {
            delete v;
        }

        funcs.clear();
        consts.clear();
        vars.clear();
    }

    void Program::Validate() {
        for( auto&& f : funcs ) {
            f->Validate();
        }
        for( auto&& c : consts ) {
            c->Validate();
        }
        for( auto&& v : vars ) {
            v->Validate();
        }
    }

    void Program::GenerateCode(std::ostream & out) {

    }

}