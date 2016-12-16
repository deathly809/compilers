
#include <ast/FunctionDefinition.hpp>

#include <ast/Block.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

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

    void FunctionDefinition::GenerateCode(std::ostream & out) const {
        
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