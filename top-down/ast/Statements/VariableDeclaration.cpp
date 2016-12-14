
#include <ast/Statements/VariableDeclaration.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

#include <iostream>

namespace ast {

    VariableDeclaration::VariableDeclaration(lexer::Lexer &lex, symtable::SymbolTable * table) : Statement(table) {
        lexer::Lexeme* c = lex.Next();
        lex.HasNext();
        if(c == nullptr) {
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", unexpected EOF");
        }

        std::cout << "A: " << *c << std::endl;
        
        switch(c->GetType()) {
            case lexer::VAR:
                variable = true;
                break;
            case lexer::CONST:
                variable = false;
                break;
            default:
                throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", expected var or const");
        }

        consumeLexemeType(c,lexer::VAR);

        name = new Identifier(lex, table);

        c = lex.Next();

        std::cout << "B: " << *c << std::endl;

        if(c->GetType() == lexer::C_EQUAL) {
            consumeLexemeType(c, lexer::C_EQUAL);
            lex.HasNext();
            value = new Expression(lex, table);
        } else {
            type = new Type(lex, table);
        }
        lex.HasNext();
    }

    VariableDeclaration::~VariableDeclaration() {
        delete name;
        delete value;
        delete type;
    }

    void VariableDeclaration::Validate() {
        
        if(!validated && value != nullptr) {
            value->Validate();
        }

        validated = true;
    }

    void VariableDeclaration::GenerateCode(std::ostream & out) {

    }

}