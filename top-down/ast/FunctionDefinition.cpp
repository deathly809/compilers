
#include <ast/FunctionDefinition.hpp>

#include <ast/Block.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    FunctionDefinition::FunctionDefinition(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        consumeLexemeType(lex.Next(),lexer::FUNC);
        
        functionName = new Identifier(lex, table);
        consumeLexemeType(lex.Next(), lexer::O_PAREN);
        
        std::unique_ptr<lexer::Lexeme>  l = lex.Next();
        if(l->GetType() != lexer::C_PAREN) {

            lex.PushBack(l);
            optParams.push_back(
                {
                    new Identifier(lex, table),
                    new Type(lex, table)
                });

            l = lex.Next();
            while(l->GetType() == lexer::COMMA) {
                lex.HasNext();
                optParams.push_back(
                    {
                        new Identifier(lex, table),
                        new Type(lex, table)
                    });
                l = lex.Next();
            }
        }
        consumeLexemeType(l,lexer::C_PAREN);

        l = lex.Next();

        if(l->GetType() != lexer::O_BRACE) {
            lex.PushBack(l);
            optRetType = new Type(lex, table);
        } else {
            consumeLexemeType(l,lexer::O_BRACE);
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

}