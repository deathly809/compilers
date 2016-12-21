
#include <ast/Expressions/FunctionCall.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <symtable/Attribute.hpp>
#include <symtable/SymbolTable.hpp>

namespace ast {

    FunctionCall::FunctionCall(lexer::Lexer& lex, symtable::SymbolTable * table ) : Ast(table), functionName(nullptr) {

        functionName = new Identifier(lex, table);
        consumeLexemeType(lex,lexer::O_PAREN);
        
        // arguments
        if(NextType(lex) != lexer::C_PAREN) {
            arguments.push_back(new Expression(lex, table));
            while(NextType(lex) == lexer::COMMA) {
                consumeLexemeType(lex,lexer::COMMA);
                arguments.push_back(new Expression(lex, table));
            }
        }
        consumeLexemeType(lex,lexer::C_PAREN);
    }

    FunctionCall::~FunctionCall() {
        delete functionName;
        for(auto && a : arguments) {
            delete a;
        }
    }

    void FunctionCall::Validate() const {
        functionName->Validate();
        for(auto && a : arguments) {
            a->Validate();
        }
    }

    std::unique_ptr<hardware::Register> FunctionCall::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        std::shared_ptr<symtable::Attribute> attr = table->Locate(functionName->GetName());

        if(!attr || attr->GetType() != symtable::FunctionAttributeType) {
            throw std::runtime_error("CodeGen: FunctionCall, no function by the name " + functionName->GetName());
        }
        std::shared_ptr<symtable::FunctionAttribute> fAttr = std::static_pointer_cast<symtable::FunctionAttribute,symtable::Attribute>(attr);
        
        for(auto && a : arguments) {
            a->GenerateCode(codeGen);
        }

        if(fAttr->IsBuiltIn()) {
            fAttr->GenerateCode(codeGen);
        } else {
            codeGen.Call(fAttr->GetLabel());            
        }

        return nullptr;
    }

    ValueType FunctionCall::ResultType() const {
        return functionName->ResultType();
    }

    std::ostream& FunctionCall::Write(std::ostream & os) const {
        os << *functionName << "(";
        if(arguments.size() > 0) {
            os << *arguments[0];
            for(unsigned int i = 1; i < arguments.size(); ++i) {
                os << ", " << *arguments[i];
            }
        }
        return os << ")";
    }
}
