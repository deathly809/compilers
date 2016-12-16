
#ifndef TYPE_HPP_
#define TYPE_HPP_

#include <ast/Ast.hpp>

namespace ast {

    enum ValueType { IntType, RealType, StringType, BoolType, IntArrayType, RealArrayType, StringArrayType, BoolArrayType, NilType}; 

    std::string & ValueTypeToString(ValueType type);

    class IntegerLiteral;

    class Type : public Ast {

        private:
            ValueType type;
            IntegerLiteral* arrayLength = nullptr;

        public:
            Type(lexer::Lexer & lex, symtable::SymbolTable * table);
            ValueType GetType() const;
            
            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

    };
}

#endif