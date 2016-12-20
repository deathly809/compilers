
#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include <ast/Ast.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class BlockDefinition;
    class FunctionDefinition;
    
    class Program : public Ast {

        private:
            std::vector<FunctionDefinition*>    funcs;
            std::vector<BlockDefinition*>       vars;

        public:
            Program(lexer::Lexer& lex, symtable::SymbolTable * table);
            Program(lexer::Lexer& lex);
            ~Program();


            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream& os) const;

    };

}

#endif