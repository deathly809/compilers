
#include <ast/Statements/VariableDeclaration.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <symtable/Attribute.hpp>
#include <symtable/SymbolTable.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

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

        std::unique_ptr<lexer::Lexeme> nameLexeme = lex.Next();
        auto tmpAttr = new symtable::VariableAttribute(nameLexeme->GetValue(), nameLexeme->GetFilename(), nameLexeme->GetLine(), nameLexeme->GetColumn(),kind,NilType);
        auto attr = std::shared_ptr<symtable::Attribute>(tmpAttr);
        lex.PushBack(nameLexeme);
        table->Insert(attr);

        name = new Identifier(lex, table);

        ValueType varType = ValueType::NilType;

        if(NextType(lex) == lexer::EQUAL) {
            consumeLexemeType(lex,lexer::EQUAL);
            value = new Expression(lex, table);
            varType = value->ResultType();
        } else {
            type = new Type(lex, table);
            varType = type->GetType();
        }

        tmpAttr->SetVariableType(varType);
        
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

    std::unique_ptr<hardware::Register> VariableDeclaration::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        if(value != nullptr) {
            return value->GenerateCode(codeGen);
        }
        return nullptr;
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