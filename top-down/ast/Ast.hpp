
#ifndef AST_HPP
#define AST_HPP

#include <ast/Util.hpp>

#include <ostream>
#include <lexer/Lexer.hpp>

#include <memory>

// #define DEBUG

#ifdef DEBUG 
    #include <iostream>
#endif


namespace hardware {
    class Register;
    class InstructionGenerator;
}


namespace symtable {
    class SymbolTable;
}


namespace ast {

    class Ast {
        public:
            /* Validate that we are correct */
            virtual void Validate() const = 0;

            /* Given an output stream we write the code generated */
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const = 0;

            virtual std::ostream& Write(std::ostream & os) const = 0;

            virtual ~Ast();

        protected:

            bool                    validated;
            symtable::SymbolTable*  table;

            Ast(symtable::SymbolTable * table);
            

    };

    std::ostream& operator<<(std::ostream & os, const Ast & ast);

}

#endif