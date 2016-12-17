
#include <ast/Program.hpp>
#include <lexer/Lexer.hpp>

#include <exception>

const int Success = 0;
const int MissingFilename = 1;
const int CompilerError = 2;

int main(int argc, char* argv[]) {

    if(argc != 2) {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return MissingFilename;
    }

    try {
        lexer::Lexer lex(argv[1]);
        ast::Program prog(lex);

        std::cout << prog << std::endl;

        prog.Validate();
        prog.GenerateCode(std::cout);

    } catch(std::exception & ex ) {
        std::cout << "compilation error" << std::endl;
        std::cout << ex.what() << std::endl;
        return CompilerError;
    }
    return Success;
}