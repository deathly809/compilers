
#include <Lexer.hpp>

#include <Lexeme.hpp>

#include <sstream>
#include <map>

namespace lexer {

    const std::map<std::string,LexemeType> Keywords = {
        {"import",IMPORT},
        {"const",CONST},
        {"var",VAR},
        {"for",LOOP},
        {"if",IF},
        {"else",ELSE},
        {"package",PACKAGE},
        {"func",FUNC},
        {"int",INT},
        {"return",RETURN},
        {"string",STRING}
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
        delete scan;
    }

    bool Lexer::HasNext() {
        if(pushedBack.size() > 0) return true;

        while(scan->HasNext() && std::isspace(scan->Next())) {
            if(scan->Next() == '\n') {
                line++;
                column = 0;
            } else {
                column++;
            }
        }
        return scan->Next() != 0;
    }

    std::string unexpectedCharacter(char  c, std::string file, int line, int column) {
        std::stringstream ss;
        ss << "in file " << file << " on line " << line << " column " << column << " unexpected character: " << c;
        return ss.str();
    }

    Lexeme* Lexer::readIdentifier() {
        std::stringstream ss;
        ss << scan->Next();
        while(scan->HasNext() && (scan->Next() == '_' || std::isalnum(scan->Next()))) {
            ss << scan->Next();
        }
        scan->PushBack();
        std::string id = ss.str();
        auto ptr = Keywords.find(id);
        if(ptr != Keywords.end()) {
            return new Lexeme(ptr->second,file,line,column);
        }
        return new Lexeme(ID,id,file,line,column);
    }

    Lexeme* Lexer::readNumber() {
        std::stringstream ss;
        ss << scan->Next();
        while(scan->HasNext() && std::isdigit(scan->Next())) {
            ss << scan->Next();
        }
        return new Lexeme(INT,ss.str(),file,line,column);
    }

    Lexeme* singleChar(char c,std::string file, int line, int column) {
        Lexeme *result = nullptr;
        switch(c){
            case ';':
                result = new Lexeme(SEMI,file,line,column);
                break;
            case '(':
                result = new Lexeme(O_PAREN,file,line,column);
                break;
            case ')':
                result = new Lexeme(C_PAREN,file,line,column);
                break;
            case '[':
                result = new Lexeme(O_BRACKET,file,line,column);
                break;
            case ']':
                result = new Lexeme(C_BRACKET,file,line,column);
                break;
            case '{':
                result = new Lexeme(O_BRACE,file,line,column);
                break;
            case '}':
                result = new Lexeme(C_BRACE,file,line,column);
                break;
            case ',':
                result = new Lexeme(COMMA,file,line,column);
                break;
            case '/':
                result = new Lexeme(DIV,file,line,column);
                break;
            case '.':
                result = new Lexeme(PERIOD,file,line,column);
                break;
            /*case ':':
                result = new Lexeme(COLON,file,line,column);
                break;
            */case '-':
                result = new Lexeme(MINUS,file,line,column);
                break;
            case '+':
                result = new Lexeme(PLUS,file,line,column);
                break;
            case '*':
                result = new Lexeme(MUL,file,line,column);
                break;
        }
        return result;
    }

    Lexeme* Lexer::Next() {

        if(pushedBack.size() > 0) {
            Lexeme* result = pushedBack.back();
            pushedBack.pop_back();
            return result;
        }
        
        char curr = scan->Next();

        if(curr == ':') {

            if(!scan->HasNext()) {
                throw std::runtime_error("unexpected EOF");
            }

            curr = scan->Next();        
            if(curr != '=') {
                throw std::runtime_error("expected = but found" + std::string(1, scan->Next()));
            }
            return new Lexeme(C_EQUAL, file, line, column);
        }

        Lexeme *result = singleChar(curr,file,line,column);
        if(result != nullptr) {
            return result;
        }

        if(curr == '=') {
            if(scan->HasNext()) {
                if(scan->Next() == '=') {
                    result = new Lexeme(D_EQUAL,file,line,column);
                } else {
                    result = new Lexeme(EQUAL,file,line,column);
                    scan->PushBack();
                }
            }
            return result;
        }

        if(curr == '<') {
            if(scan->HasNext()) {
                if(scan->Next() == '=') {
                    result = new Lexeme(LTE,file,line,column);
                } else {
                    result = new Lexeme(LT,file,line,column);
                    scan->PushBack();
                }
            }
            return result;
        }

        if(curr == '>') {
            if(scan->HasNext()) {
                if(scan->Next() == '=') {
                    result = new Lexeme(GTE,file,line,column);
                } else {
                    result = new Lexeme(GT,file,line,column);
                    scan->PushBack();
                }
            }
            return result;
        }

        if(curr == '!') {
            if(scan->HasNext()) {
                if(scan->Next() == '=') {
                    result = new Lexeme(NE,file,line,column);
                } else {
                    result = new Lexeme(BANG,file,line,column);
                    scan->PushBack();
                }
            }
            return result;
        }

        if(curr == '&') {
            result = new Lexeme(AND,file,line,column);
            if(scan->HasNext()) {
                if(scan->Next() != '&') {
                    std::stringstream ss;
                    ss << "Expected & but found " << scan->Next();
                    throw std::runtime_error(ss.str());
                }
            } else {
                throw std::runtime_error("Expected & but found EOF");
            }
            return result;
        }

        // string
        if(curr == '"') {
            std::stringstream ss;
            bool escape = false;
            bool closed = false;
            while(!closed && scan->HasNext()) {
                if(escape) {
                    switch(scan->Next()) {
                        case 'n':
                            ss << '\n';
                            break;
                        case 'r':
                            ss << '\r';
                            break;
                        case 'b':
                            ss << '\b';
                            break; 
                        case 't':
                            ss << '\t';
                            break;
                        default:
                            ss << scan->Next();
                            break;
                    }
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
            return new Lexeme(STRING,ss.str(),file,line,column);
        }

        if(curr == '_' || std::isalpha(curr)) {
            return readIdentifier();
        }

        if(std::isdigit(curr)) {
            return readNumber();
        }

        if(curr == 0) {
            return nullptr;
        }

        throw std::runtime_error(unexpectedCharacter(curr,file,line,column));
    }

    void Lexer::PushBack(Lexeme * l) {
        pushedBack.push_back(l);
    }

}

