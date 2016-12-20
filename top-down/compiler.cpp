
#include <ast/Program.hpp>
#include <lexer/Lexer.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <exception>
#include <memory>

const int Success = 0;
const int MissingFilename = 1;
const int CompilerError = 2;

#define CATCH

int main(int argc, char* argv[]) {

    if(argc != 2) {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return MissingFilename;
    }

#ifdef CATCH
    try {
#endif
        lexer::Lexer lex(argv[1]);
        ast::Program prog(lex);

        prog.Validate();
        hardware::InstructionGenerator gen(std::cout);
        auto ptr = prog.GenerateCode(gen);
        if(ptr) {
            std::cout << "this should have been null" << std::endl;
        }

        std::cout << prog << std::endl;

#ifdef CATCH
    } catch(std::exception & ex ) {
        std::cout << "compilation error" << std::endl;
        std::cout << ex.what() << std::endl;
        return CompilerError;
    }
#endif
    return Success;
}
