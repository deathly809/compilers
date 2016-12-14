
#ifndef AST_HPP
#define AST_HPP

#include <ast/Util.hpp>

#include <ostream>
#include <Lexer.hpp>

#include <symtable/SymbolTable.hpp>


#ifdef DEBUG 
    #include <iostream>
#endif


namespace ast {

    class Ast {
        public:
            /* Validate that we are correct */
            virtual void Validate() = 0;

            /* Given an output stream we write the code generated */
            virtual void GenerateCode(std::ostream & out) = 0;
            
        protected:

            bool                    validated;
            symtable::SymbolTable*  table;

            Ast(symtable::SymbolTable * table);
            virtual ~Ast();

    };

}

#endif