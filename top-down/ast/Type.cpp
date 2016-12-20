
#include <ast/Type.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <ast/UnexpectedToken.hpp>

#include <ast/Expressions/Literals/IntegerLiteral.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <map>

namespace ast {

    static std::map<ValueType,std::string> valueTypeMapping = {
        {CharType,          "CHAR"},
        {IntType,           "INT"},
        {RealType,          "REAL"},
        {StringType,        "STRING"},
        {BoolType,          "BOOLEAN"},
        {CharArrayType,     "[]CHAR]"},
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
            switch(NextType(lex)) {
                case lexer::CHARTYPE:
                    type = CharArrayType;
                    break;
                case lexer::INTTYPE:
                    type = IntArrayType;
                    break;
                case lexer::REALTYPE:
                    type = RealArrayType;
                    break;
                case lexer::STRINGTYPE:
                    type = StringArrayType;
                    break;
                case lexer::BOOLTYPE:
                    type = BoolArrayType;
                    break;
                default: 
                    throw UnexpectedToken(lex.Next(),__FILE__,__LINE__);
            }
        } else {
            switch(NextType(lex)) {
                case lexer::CHARTYPE:
                    type = CharType;
                    break;
                case lexer::INTTYPE:
                    type = IntType;
                    break;
                case lexer::REALTYPE:
                    type = RealType;
                    break;
                case lexer::STRINGTYPE:
                    type = StringType;
                    break;
                case lexer::BOOLTYPE:
                    type = BoolType;
                    break;
                default: 
                    throw UnexpectedToken(lex.Next(),__FILE__,__LINE__);
            }
        }
        lex.Next();
        lex.HasNext();
    }

    void Type::Validate() const {
    }

    ValueType Type::GetType() const {
        return type;
    }

    std::unique_ptr<hardware::Register> Type::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        return nullptr;
    }


    std::ostream& Type::Write(std::ostream & os) const {
        return os << ValueTypeToString(GetType());
    }
}