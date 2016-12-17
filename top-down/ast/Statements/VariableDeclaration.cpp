
#include <ast/Statements/VariableDeclaration.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <symtable/Attribute.hpp>
#include <symtable/SymbolTable.hpp>

#include <iostream>
#include <memory>

namespace ast {


    VariableDeclaration::VariableDeclaration(lexer::Lexer &lex, symtable::SymbolTable * table) : Statement(table) {
        switch(NextType(lex)) {
            case lexer::VAR:
                consumeLexemeType(lex,lexer::VAR);
                variable = true;
                break;
            case lexer::CONST:
                consumeLexemeType(lex,lexer::CONST);
                variable = false;
                break;
            default:
                throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", expected var or const");
        }

        symtable::IdentifierKind kind = variable? symtable::Var:symtable::Const;


        name = new Identifier(lex, table);

        if(NextType(lex) == lexer::EQUAL) {
            consumeLexemeType(lex,lexer::EQUAL);
            value = new Expression(lex, table);
        } else {
            type = new Type(lex, table);
            table->Insert(
                std::shared_ptr<symtable::Attribute>(
                    new symtable::VariableAttribute(name->GetName(),kind,type->GetType())
                )
            );

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
            os << "= " << *value;
        } else {
            os << *type;
        }
        return os;
    }

}