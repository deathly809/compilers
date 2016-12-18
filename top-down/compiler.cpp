
#include <ast/Program.hpp>
#include <lexer/Lexer.hpp>

#include <hardware/Register.hpp>

#include <exception>
#include <memory>

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

        prog.Validate();
        auto ptr = prog.GenerateCode(std::cout);
        if(ptr) {
            std::cout << "this should have been null" << std::endl;
        }

        std::cout << prog << std::endl;



    } catch(std::exception & ex ) {
        std::cout << "compilation error" << std::endl;
        std::cout << ex.what() << std::endl;
        return CompilerError;
    }
    return Success;
}
