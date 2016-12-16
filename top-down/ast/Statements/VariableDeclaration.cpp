
#include <ast/Statements/VariableDeclaration.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

#include <iostream>

namespace ast {

    VariableDeclaration::VariableDeclaration(lexer::Lexer &lex, symtable::SymbolTable * table) : Statement(table) {
        switch(NextType(lex)) {
            case lexer::VAR:
                variable = true;
                break;
            case lexer::CONST:
                variable = false;
                break;
            default:
                throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", expected var or const");
        }

        lex.Next();
        lex.HasNext();

        name = new Identifier(lex, table);

        if(NextType(lex) == lexer::C_EQUAL) {
            
            consumeLexemeType(lex.Next(),lexer::C_EQUAL);
            lex.HasNext();

            value = new Expression(lex, table);
        } else {
            type = new Type(lex, table);
        }
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

    std::ostream& VariableDeclaration::Write(std::ostream & os) const {
        if(variable) {
            os << "var ";
        } else {
            os << "const ";
        }

        os << *name << " ";

        if(type == nullptr) {
            os << ":= " << *value;
        } else {
            os << *type;
        }
        return os;
    }

}