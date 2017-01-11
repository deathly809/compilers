
#include <lexer/Lexer.hpp>
#include <lexer/Lexeme.hpp>

#include <sstream>
#include <map>

namespace lexer {

    void checkEOF(bool test) {
        if(!test) throw std::runtime_error("unexpected EOF");
    }

    const std::map<std::string,LexemeType> Keywords = {
        {"import",IMPORT},
        {"const",CONST},
        {"var",VAR},
        {"for",LOOP},
        {"if",IF},
        {"else",ELSE},
        {"package",PACKAGE},
        {"func",FUNC},
        {"return",RETURN},
        {"char",CHARTYPE},
        {"int",INTTYPE},
        {"real",REALTYPE},
        {"string",STRINGTYPE},
        {"bool",BOOLTYPE},
        {"true",BOOL},
        {"false",BOOL},
        {"type",TYPE}
    };


    Lexer::Lexer(std::string filename) { 
        line = 1;
        column = 0;
        file = filename;
        scan = new Scanner(filename);
    }

    Lexer::Lexer(Scanner *input) {
        line = 1;
        column = 0;
        file = "memory";
        scan = input;
    }

    Lexer::~Lexer() {
        // Make sure we free anything pushed back
        pushedBack.clear();
        delete scan;
    }

    bool Lexer::HasNext() {
        if(pushedBack.size() > 0) return true;

        do {
            while(scan->HasNext() && std::isspace(scan->Next())) {
                if(scan->Next() == '\n') {
                    line++;
                    column = 0;
                } else {
                    column++;
                }
            }
            if(scan->Next() == '#') {
                while(scan->HasNext() && scan->Next() != '\n');
            } else {
                break;
            }
        } while(true);

        return scan->Next() != 0;
    }

    std::string unexpectedCharacter(char  c, std::string file, int line, int column,int line_here) {
        std::stringstream ss;
        ss << "["<< line_here << "]" << "in file " << file << " on line " << line << " column " << column << " unexpected character: " << c;
        return ss.str();
    }

    char getEscaped(char c) {
        switch(c) {
            case 'n':
                return '\n';
            case 'r':
                return '\r';
            case 'b':
                return '\b';
            case 't':
                return '\t';
            default:
                return c;
        }
    }

    std::unique_ptr<Lexeme> Lexer::readString() {
        std::stringstream ss;
        bool escape = false;
        bool closed = false;
        while(!closed && scan->HasNext()) {
            if(escape) {
                ss << getEscaped(scan->Next());
                escape = false;
            } else if(scan->Next() == '\\') {
                escape = true;
            } else if(scan->Next() == '"') {
                closed = true;
            } else {
                ss << scan->Next();
            }
        }

        if(!closed) {
            std::stringstream ss;
            ss << "in file " << file << " on line " << line << " column " << column << ": unclosed string";
            throw std::runtime_error(ss.str());
        }

        return std::unique_ptr<Lexeme>( new Lexeme(STRING,ss.str(),file,line,column));
    }

    std::unique_ptr<Lexeme> Lexer::readIdentifier() {

        std::stringstream ss;
        ss << scan->Next();
        while(scan->HasNext() && (scan->Next() == '_' || std::isalnum(scan->Next()))) {
            ss << scan->Next();
        }

        // we read something, push it back 
        scan->PushBack();
        std::string id = ss.str();
        auto ptr = Keywords.find(id);
        if(ptr != Keywords.end()) {
            return std::unique_ptr<Lexeme>(new Lexeme(ptr->second,id,file,line,column));
        }
        return std::unique_ptr<Lexeme>(new Lexeme(ID,id,file,line,column));
    }

    std::unique_ptr<Lexeme> Lexer::readCharacter() {
        std::stringstream ss;

        ss << scan->Next(); // single quote
        checkEOF(scan->HasNext());

        char c = scan->Next();
        if(c == '\\') {
            checkEOF(scan->HasNext());
            c = getEscaped(scan->Next());
        }
        ss << c;

        checkEOF(scan->HasNext());

        c = scan->Next();
        if(c != '\'') {
            std::stringstream ss;
            ss << "in file " << file << " on line " << line << " column " << column << ": unclosed character";
            throw std::runtime_error(ss.str());
        }

        return std::unique_ptr<Lexeme>(new Lexeme(CHAR,ss.str(),file,line,column));
    }

    std::unique_ptr<Lexeme> Lexer::readNumber() {
        std::stringstream ss;
        ss << scan->Next();
        while(scan->HasNext() && std::isdigit(scan->Next())) {
            ss << scan->Next();
        }
        scan->PushBack();
        return std::unique_ptr<Lexeme>(new Lexeme(INT,ss.str(),file,line,column));
    }

    std::map<char,LexemeType> singleCharacters = {
        {';',SEMI},
        {'(',O_PAREN},
        {')',C_PAREN},
        {'{',O_BRACE},
        {'}',C_BRACE},
        {'[',O_BRACKET},
        {']',C_BRACKET},
        {',',COMMA},
        {'.',PERIOD},
        {'*',MUL},
        {'/',DIV},
        {'+',PLUS},
        {'-',MINUS},
        {'%',MOD},
        {'|',OR},
        {'&',AND},
        {';',SEMI},
    };

    std::unique_ptr<Lexeme> singleChar(char c,std::string file, int line, int column) {
        std::unique_ptr<Lexeme> result = nullptr;
        const auto ptr = singleCharacters.find(c);
        if(ptr != singleCharacters.end()) {
            result = std::move(std::unique_ptr<Lexeme>(new Lexeme(ptr->second,file,line,column)));
        }
        return result;
    }

    std::unique_ptr<Lexeme> Lexer::Next() {
        std::unique_ptr<Lexeme> result = nullptr;

        if(pushedBack.size() > 0) {
            result = std::move(pushedBack.back());
            pushedBack.pop_back();
        } else {
            char curr = scan->Next();

            result = singleChar(curr,file,line,column);
            if(result != nullptr) {
                /* Empty */
            } else if(curr == '_' || std::isalpha(curr)) {
                result = readIdentifier();
            } else if(std::isdigit(curr)) {
                result = readNumber();
            } else {
                switch (curr) {
                    case 0:
                        result = std::move(std::unique_ptr<Lexeme>(new Lexeme(ENDFILE,file,line,column)));
                        break;
                    case ':':
                    if(!scan->HasNext()) {
                        throw std::runtime_error("unexpected EOF");
                    }
                    if(scan->Next() != '=') {
                        throw std::runtime_error("expected = but found " + std::string(1, scan->Next()));
                    }
                    
                    result = std::move(std::unique_ptr<Lexeme>(new Lexeme(C_EQUAL, file, line, column)));
                    break;
                    case '=':
                        if(scan->HasNext()) {
                            if(scan->Next() == '=') {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(D_EQUAL,file,line,column)));
                            } else {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(EQUAL,file,line,column)));
                                scan->PushBack();
                            }
                        }
                        break;
                    case '<':
                            if(scan->HasNext()) {
                            if(scan->Next() == '=') {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(LTE,file,line,column)));
                            } else {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(LT,file,line,column)));
                                scan->PushBack();
                            }
                        }
                        break;
                    case '>':
                        if(scan->HasNext()) {
                            if(scan->Next() == '=') {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(GTE,file,line,column)));
                            } else {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(GT,file,line,column)));
                                scan->PushBack();
                            }
                        }
                        break;
                    case '!':
                            if(scan->HasNext()) {
                            if(scan->Next() == '=') {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(NE,file,line,column)));
                            } else {
                                result = std::move(std::unique_ptr<Lexeme>(new Lexeme(BANG,file,line,column)));
                                scan->PushBack();
                            }
                        }
                        break;
                    case '"':
                        result = readString();
                        break;
                    case '\'':
                        result = readCharacter();
                        break;
                    default:
                        throw std::runtime_error(unexpectedCharacter(curr,file,line,column,__LINE__));
                        break;
                }
            }
        }
        return result;
    }

    void Lexer::PushBack(std::unique_ptr<Lexeme> & l) {
        pushedBack.push_back(std::move(l));
    }

}

