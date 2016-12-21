
#include <ast/FunctionDefinition.hpp>

#include <ast/Block.hpp>
#include <ast/Identifier.hpp>
#include <ast/Type.hpp>

#include <symtable/Attribute.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

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

        for(auto && opt : optParams) {
            opt.ident->Validate();
            opt.type->Validate();
        }

        auto retType = ValueType::NilType;
        if(optRetType != nullptr) {
            optRetType->Validate();
            retType = optRetType->GetType();
        }

        auto attr = std::shared_ptr<symtable::FunctionAttribute>(new symtable::FunctionAttribute(functionName->GetName(), functionName->GetFilename(), functionName->GetLine(), functionName->GetColumn(),retType));
        table->Insert(attr);

        functionName->Validate();

        block->Validate();

    }

    std::unique_ptr<hardware::Register> FunctionDefinition::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        std::string label = codeGen.GenerateLabel();
        std::shared_ptr<symtable::Attribute> attr = table->Locate(functionName->GetName());
        if(attr) {
            std::shared_ptr<symtable::FunctionAttribute> fAttr = std::static_pointer_cast<symtable::FunctionAttribute,symtable::Attribute>(attr);
            fAttr->SetLabel(label);
            codeGen.WriteLabel(label);
            codeGen.NOp();
            codeGen.Proc(1);
            /*
            for(auto && opt : optParams) {
                opt.ident->Validate();
                opt.type->Validate();
            }
            
            if(optRetType != nullptr) {
                optRetType->Validate();
            }
            */
            block->GenerateCode(codeGen);
            codeGen.Ret(1);
        } else {
            throw std::runtime_error("CodeGen: FunctionDefinition");
        }
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