
#include <ast/Statements/VariableDeclaration.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

#include <iostream>

namespace ast {

    VariableDeclaration::VariableDeclaration(lexer::Lexer &lex, symtable::SymbolTable * table) : Statement(table) {
        std::unique_ptr<lexer::Lexeme> c = lex.Next();
        if(c == nullptr) {
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", unexpected EOF");
        }
        
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
        lex.HasNext();

        name = new Identifier(lex, table);

        if(NextType(lex) == lexer::C_EQUAL) {
            lex.Next();
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

    void VariableDeclaration::Validate() const {
        if(value != nullptr) {
            value->Validate();
        }
    }

    void VariableDeclaration::GenerateCode(std::ostream & out) const {

    }

    std::ostream& operator<<(std::ostream & os, const VariableDeclaration & varDef) {
        if(varDef.variable) {
            os << "var ";
        } else {
            os << "const ";
        }

        os << *varDef.name << " ";

        if(varDef.type == nullptr) {
            os << ":= " << *varDef.value;
        } else {
            os << *varDef.type;
        }
        return os;
    }

}