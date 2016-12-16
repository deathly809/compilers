
#ifndef SCANNER_HPP_
#define SCANNER_HPP_

#include <string>
#include <istream>

class Scanner {
    public:
        Scanner(std::string filename);
        Scanner(std::istream & input);
        ~Scanner();
        bool HasNext();
        char Next();
        void PushBack();
    private:
        int pos;
        int size;
        char* buffer;
};

#endif