
#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include <ast/Ast.hpp>

namespace symtable {
    class SymbolTable;
}

namespace ast {

    class ConstantBlock;
    class FunctionDefinition;
    class VariableBlock;
    
    class Program : public Ast {

        private:
            std::vector<FunctionDefinition*>    funcs;
            std::vector<ConstantBlock*>         consts;
            std::vector<VariableBlock*>         vars;

        public:
            Program(lexer::Lexer& lex);
            ~Program();


            virtual void Validate();
            virtual void GenerateCode(std::ostream & out);

    };

}

#endif