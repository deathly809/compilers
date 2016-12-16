
#include <ast/Type.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    static std::map<ValueType,std::string> valueTypeMapping = {
        {IntType,           "INT"},
        {RealType,          "REAL"},
        {StringType,        "STRING"},
        {BoolType,          "BOOLEAN"},
        {IntArrayType,      "[]INT"},
        {RealArrayType,     "[]REAL"},
        {StringArrayType,   "[]STRING"},
        {BoolArrayType,     "[]BOOLEAN"},
        {NilType,           "NIL"}
    };

    std::string & ValueTypeToString(ValueType type) {
        return valueTypeMapping[type];
    }

    Type::Type(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        std::unique_ptr<lexer::Lexeme> l = lex.Next();
        lex.HasNext();

        if(l->GetValue() == "int") {
            type = IntType;
        } else if(l->GetValue() == "real") {
            type = RealType;
        } else if(l->GetValue() == "string") {
            type = StringType;
        } else if(l->GetValue() == "bool") {
            type = BoolType;
        } else { 
            throw std::runtime_error("expected a type: " + LexemeTypeToString(NextType(lex)));
        }
    }

    void Type::Validate() const {
    }

    ValueType Type::GetType() const {
        return type;
    }

    void Type::GenerateCode(std::ostream & out) const {

    }


    std::ostream& operator<<(std::ostream & os, const Type & type) {
        return os << ValueTypeToString(type.GetType());
    }
}