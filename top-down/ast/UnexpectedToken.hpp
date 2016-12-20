
#ifndef UNEXPECTEDTOKEN_HPP_
#define UNEXPECTEDTOKEN_HPP_

#include <exception>

namespace ast {

    class UnexpectedToken : public std::runtime_error {

        public:
            UnexpectedToken(std::unique_ptr<lexer::Lexeme> & lexeme, const char* file, int line) : std::runtime_error("unexpected token"), file(std::string(file)), line(line), lexeme(std::move(lexeme)) {
                /* Empty */
            }
            UnexpectedToken(std::unique_ptr<lexer::Lexeme> && lexeme, const char* file, int line) : std::runtime_error("unexpected token"), file(std::string(file)), line(line), lexeme(std::move(lexeme)) {
                /* Empty */
            }

            virtual const char* what() const throw() {
                std::ostringstream cnvt( "" );
                
                cnvt << runtime_error::what() << ": " << file << "(" << line << ") " << std::endl;
                if(lexeme) {
                    cnvt << *lexeme; 
                }
                std::string s = cnvt.str();
                s.copy(buffer,s.size());
                buffer[s.size()] = '\0';
                return buffer;
            }

        private:
            
        private:
            const std::string file;
            const int line;
            std::unique_ptr<lexer::Lexeme> lexeme;
            mutable char buffer[512];

    };

}

#endif