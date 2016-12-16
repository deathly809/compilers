
#include <lexer/Scanner.hpp>

#include <algorithm>
#include <vector>
#include <fstream>

Scanner::Scanner(std::string filename) : pos(-1), size(0), buffer(nullptr) {
    std::ifstream t(filename);
    t.seekg(0, std::ios::end);
    size = t.tellg();
    buffer = new char[size];
    t.seekg(0);
    t.read(buffer, size); 
}

Scanner::Scanner(std::istream & in) : pos(-1), size(0), buffer(nullptr) {
    char c;
    std::vector<char> buff;
    while(in.get(c)) {
        buff.push_back(c);
    }

    size = buff.size();
    buffer = new char[size];
    

    std::copy(buff.begin(),buff.end(),buffer);
}

Scanner::~Scanner() {
    delete[] buffer;
}

bool Scanner::HasNext() {
    pos++;
    return pos < size;
}

char Scanner::Next() {
    if(pos < size) {
        return buffer[pos];
    }
    return 0;
}

void Scanner::PushBack() {
    if(pos >= 0) pos--;
}
