
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

        kind = variable? symtable::Var:symtable::Const;

        name = new Identifier(lex, table);

        
        if(NextType(lex) == lexer::EQUAL) {
            consumeLexemeType(lex,lexer::EQUAL);
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
        
        ValueType varType = ValueType::NilType;
        
        if(value != nullptr) {
            try {
                value->Validate();
            } catch(std::exception &e) {

            }
            varType = value->ResultType();
        } else {
            varType = type->GetType();
        }

        int size = 1;
        if(type != nullptr) size = type->GetSize();
        auto attr = std::shared_ptr<symtable::Attribute>(new symtable::VariableAttribute(name->GetName(), name->GetFilename(), name->GetLine(), name->GetColumn(),kind,varType, size));
        table->Insert(attr);

        name->Validate();

        if(value != nullptr) {
            value->Validate();
        }
    }

    std::unique_ptr<hardware::Register> VariableDeclaration::GenerateCode(hardware::InstructionGenerator & codeGen) const {

        if(value != nullptr) {
            value->GenerateCode(codeGen);
        
            size_t scope = name->ScopeID();
            size_t pos = name->ScopePosition();
            codeGen.St(
                scope,
                pos + 1
            );
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