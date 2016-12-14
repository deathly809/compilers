
#ifndef LEXEME_HPP_
#define LEXEME_HPP_

#include <LexemeTypes.hpp>

namespace lexer {

    class Lexeme {

        public:

            Lexeme(LexemeType type, std::string val, std::string file, int line, int column );
            Lexeme(LexemeType type, std::string file, int line, int column );

            const std::string& GetFileName() const;
            
            LexemeType GetType() const;

            int GetLine() const;
            
            int GetColumn() const;
            
            const std::string& GetValue() const;

        private:
            
            const LexemeType type;
            const std::string value;
            const int line,column;
            const std::string file; 

    };

    std::ostream& operator<<(std::ostream& os, const Lexeme& lex);

}

#endif
