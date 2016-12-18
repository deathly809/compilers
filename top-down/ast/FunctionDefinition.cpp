
#include <ast/FunctionDefinition.hpp>

#include <ast/Block.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <symtable/Attribute.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>

namespace ast {

    // func ID ( OPT_PARAMS ) OPT_RET_TYPE BLOCK
    FunctionDefinition::FunctionDefinition(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        consumeLexemeType(lex,lexer::FUNC);

        functionName = new Identifier(lex, table);

        consumeLexemeType(lex, lexer::O_PAREN);
        
        if(NextType(lex) != lexer::C_PAREN) {
            optParams.push_back(
                {
                    new Identifier(lex, table),
                    new Type(lex, table)
                });

            while(NextType(lex) == lexer::COMMA) {
                consumeLexemeType(lex,lexer::COMMA);
                optParams.push_back(
                    {
                        new Identifier(lex, table),
                        new Type(lex, table)
                    });
                
            }
        }
        consumeLexemeType(lex,lexer::C_PAREN);

        if(NextType(lex) != lexer::O_BRACE) {
            optRetType = new Type(lex, table);
        }

        ValueType retType = NilType;
        if(optRetType != nullptr) {
            retType = optRetType->GetType();
        }

        table->Insert(
            std::shared_ptr<symtable::Attribute>(
                new symtable::FunctionAttribute(functionName->GetName(), functionName->GetFilename(), functionName->GetLine(), functionName->GetColumn(), retType)
            )
        );


        block = new Block(lex, table);
    }

    FunctionDefinition::~FunctionDefinition() {
        delete functionName;
        delete optRetType;
        delete block;
        for(auto && p : optParams) {
            delete p.ident;
            delete p.type;
        }
        optParams.clear();
    }

    void FunctionDefinition::Validate() const {
        functionName->Validate();
        for(auto && opt : optParams) {
            opt.ident->Validate();
            opt.type->Validate();
        }
        if(optRetType != nullptr) {
            optRetType->Validate();
        }
        block->Validate();
    }

    std::unique_ptr<hardware::Register> FunctionDefinition::GenerateCode(std::ostream & out) const {
        return nullptr;
    }

    std::ostream& FunctionDefinition::Write(std::ostream & os) const {
        os << "func " << *functionName << "(";
        
        if(optParams.size() > 0) {
            os << *optParams[0].ident << " " << *optParams[0].type;
            for(unsigned int i = 1; i < optParams.size(); ++i) {
                os << ", " << *optParams[i].ident << " " << *optParams[i].type;    
            }
        }
        os << ") ";

        if( optRetType != nullptr) {
            os << *optRetType << " ";
        }
        return os << *block;
    }

}