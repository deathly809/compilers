
#include <ast/Program.hpp>

#include <ast/FunctionDefinition.hpp>
#include <ast/BlockDefinitions.hpp>

#include <symtable/SymbolTable.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <ast/UnexpectedToken.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    Program::Program(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        lex.HasNext();
        while(true) {
            switch(NextType(lex)) {
                case lexer::FUNC:
                    funcs.push_back(new FunctionDefinition(lex, table));
                    break;
                case lexer::CONST:
                case lexer::VAR:
                    vars.push_back(new BlockDefinition(lex, table));
                    break;
                case lexer::ENDFILE:
                    return;
                default:
                    throw UnexpectedToken(lex.Next(),__FILE__,__LINE__);
            }
        }
    }

    Program::Program(lexer::Lexer & lex) : Ast(new symtable::SymbolTable()) {
        lex.HasNext();
        while(true) {
            switch(NextType(lex)) {
                case lexer::FUNC:
                    funcs.push_back(new FunctionDefinition(lex, table));
                    break;
                case lexer::CONST:
                case lexer::VAR:
                    vars.push_back(new BlockDefinition(lex, table));
                    break;
                case lexer::ENDFILE:
                    return;
                default:
                    throw UnexpectedToken(lex.Next(),__FILE__,__LINE__);
            }
        }
    }

    Program::~Program() {
        for( auto&& f : funcs ) {
            delete f;
        }
        for( auto&& v : vars ) {
            delete v;
        }

        funcs.clear();
        vars.clear();
    }

    void Program::Validate() const {
        for( auto&& f : funcs ) {
            f->Validate();
        }
        for( auto&& v : vars ) {
            v->Validate();
        }
    }

    std::unique_ptr<hardware::Register> Program::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        std::string bottomLabel = codeGen.GenerateLabel();
        codeGen.Init();

        int variables = table->CountType(symtable::VariableAttributeType);

        if(variables > 0) {
            codeGen.Alloc(variables);
        }

        for( auto&& v : vars ) {
            v->GenerateCode(codeGen);
        }

        codeGen.Jmp(bottomLabel);

        for( auto&& f : funcs ) {
            f->GenerateCode(codeGen);
        }

        codeGen.WriteLabel(bottomLabel);

        auto ptr = table->Locate("Main");
        if(ptr) {
            std::string mainLabel = std::static_pointer_cast<symtable::FunctionAttribute,symtable::Attribute>(ptr)->GetLabel();
        codeGen.Call(mainLabel);
        } else {
            throw std::runtime_error("missing Main method");
        }

        if(variables > 0) {
            codeGen.Alloc(-variables);
        }
        codeGen.Halt();
        return nullptr;
    }

    std::ostream& Program::Write(std::ostream& os) const {
        for( auto && v : vars) {
            os << *v << std::endl;
        }
        for( auto && v : funcs) {
            os << *v << std::endl;
        }
        return os;
    }

}