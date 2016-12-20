
#ifndef TYPE_HPP_
#define TYPE_HPP_

#include <ast/Ast.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    enum ValueType {
        CharType, IntType, RealType, StringType, BoolType,
        CharArrayType, IntArrayType, RealArrayType, StringArrayType, BoolArrayType, NilType
    };

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
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

    };
}

#endif