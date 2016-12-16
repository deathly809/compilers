
#include <ast/Type.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <ast/UnexpectedToken.hpp>

#include <ast/Expressions/IntegerLiteral.hpp>

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
        if(NextType(lex) ==lexer::O_BRACKET) {
            consumeLexemeType(lex,lexer::O_BRACKET);
            if(NextType(lex) != lexer::C_BRACKET) {
                arrayLength = new IntegerLiteral(lex,table);
            }
            consumeLexemeType(lex,lexer::C_BRACKET);

            auto l = lex.Next();
            

            if(l->GetValue() == "int") {
                type = IntArrayType;
            } else if(l->GetValue() == "real") {
                type = RealArrayType;
            } else if(l->GetValue() == "string") {
                type = StringArrayType;
            } else if(l->GetValue() == "bool") {
                type = BoolArrayType;
            } else { 
                throw UnexpectedToken(lex.Next(),__FILE__,__LINE__);
            }
        } else {
            auto l = lex.Next();

            if(l->GetValue() == "int") {
                type = IntType;
            } else if(l->GetValue() == "real") {
                type = RealType;
            } else if(l->GetValue() == "string") {
                type = StringType;
            } else if(l->GetValue() == "bool") {
                type = BoolType;
            } else { 
                throw UnexpectedToken(lex.Next(),__FILE__,__LINE__);
            }
        }
        lex.HasNext();
    }

    void Type::Validate() const {
    }

    ValueType Type::GetType() const {
        return type;
    }

    void Type::GenerateCode(std::ostream & out) const {

    }


    std::ostream& Type::Write(std::ostream & os) const {
        return os << ValueTypeToString(GetType());
    }
}