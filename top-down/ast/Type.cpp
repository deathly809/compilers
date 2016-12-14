
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
        lexer::Lexeme* c = lex.Next();
        switch(c->GetType()) {
            case lexer::INT:
                type = IntType;
                break;
            case lexer::REAL:
                type = RealType;
                break;
            case lexer::STRING:
                type = StringType;
                break;
            case lexer::BOOL:
                type = BoolType;
                break;
            default:
                throw std::runtime_error("expected a type, found " + c->GetValue() + " with type " + LexemeTypeToString(c->GetType()));
        }
        delete c;
        lex.HasNext();
    }

    void Type::Validate() {
    }

    ValueType Type::GetType() {
        return type;
    }

    void Type::GenerateCode(std::ostream & out) {

    }
}