
#include <lexer/Lexeme.hpp>

#include <ostream>

namespace lexer {

    Lexeme::Lexeme(LexemeType type, std::string val, std::string file, int line, int column ) : type(type), value(val),line(line),column(column), file(file) {
        /* Empty */
    }

    Lexeme::Lexeme(LexemeType type, std::string file, int line, int column ) : type(type), value("keyword"), line(line),column(column), file(file) {
        /* Empty */
    }

    const std::string& Lexeme::GetFilename() const { 
        return file;
    }
    
    LexemeType Lexeme::GetType() const { 
        return type;
    }

    int Lexeme::GetLine() const {
        return line;
    }
    
    int Lexeme::GetColumn() const {
        return column;
    }
    
    const std::string& Lexeme::GetValue() const {
        return value;
    }


    std::ostream& operator<<(std::ostream& os, const Lexeme& lex) {
        return os << "<" << LexemeTypeToString(lex.GetType()) << ":" << lex.GetValue() << ">";
    }

}
