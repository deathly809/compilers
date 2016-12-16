
#ifndef AST_HPP
#define AST_HPP

#include <ast/Util.hpp>

#include <ostream>
#include <Lexer.hpp>

#include <symtable/SymbolTable.hpp>

// #define DEBUG

#ifdef DEBUG 
    #include <iostream>
#endif


namespace ast {

    class Ast {
        public:
            /* Validate that we are correct */
            virtual void Validate() const = 0;

            /* Given an output stream we write the code generated */
            virtual void GenerateCode(std::ostream & out) const = 0;

            virtual std::ostream& Write(std::ostream & os) const = 0;

        protected:

            bool                    validated;
            symtable::SymbolTable*  table;

            Ast(symtable::SymbolTable * table);
            virtual ~Ast();

    };

    std::ostream& operator<<(std::ostream & os, const Ast & ast);

}

#endif