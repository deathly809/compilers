

#ifndef RUNNER_HPP_
#define RUNNER_HPP_

#include <symtable/SymbolTable.hpp>
#include <lexer/Lexer.hpp>

#include <string>
#include <sstream>

template<class T>
void run(std::string input, bool print = false) {
    std::stringstream ss;
    ss << input;
    lexer::Lexer lex(new Scanner(ss));
    symtable::SymbolTable table;
    T expr(lex, &table);
    if(print) {
        std::cout << input << " : " << expr << std::endl;
    }
}

#endif