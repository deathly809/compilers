
#include <ast/Program.hpp>
#include <lexer/Lexer.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <symtable/Attribute.hpp>
#include <symtable/SymbolTable.hpp>

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
        symtable::SymbolTable table;
        hardware::InstructionGenerator gen(std::cout);

        std::function<void(hardware::InstructionGenerator&)> printInt = [](hardware::InstructionGenerator & f) { f.Out(); };
        std::function<void(hardware::InstructionGenerator&)> readInt = [](hardware::InstructionGenerator & f) { f.In(); };

        table.Insert(
            std::shared_ptr<symtable::Attribute>(
                new symtable::FunctionAttribute(printInt,"printInt", ast::ValueType::NilType)
            )
        );

        table.Insert(
            std::shared_ptr<symtable::Attribute>(
                new symtable::FunctionAttribute(readInt,"readInt", ast::ValueType::IntType)
            )
        );


        ast::Program prog(lex,&table);

        prog.Validate();


        auto ptr = prog.GenerateCode(gen);
        if(ptr) {
            std::cout << "this should have been null" << std::endl;
        }

#ifdef CATCH
    } catch(std::exception & ex ) {
        std::cout << "compilation error" << std::endl;
        std::cout << ex.what() << std::endl;
        return CompilerError;
    }
#endif
    return Success;
}
