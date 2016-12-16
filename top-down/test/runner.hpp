

#ifndef RUNNER_HPP_
#define RUNNER_HPP_

#include <symtable/SymbolTable.hpp>
#include <Lexer.hpp>

#include <string>
#include <sstream>

template<class T>
void run(std::string input) {
    std::stringstream ss;
    ss << input;
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    T expr(lex, &table);
    std::cout << input << " : " << expr << std::endl;
}

#endif