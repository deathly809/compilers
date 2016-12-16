
#include <LexemeTypes.hpp>

#include <string>
#include <fstream>
#include <memory>

namespace lexer {
    class Lexer;
    class Lexeme;
    
}

namespace parser {

    class Node;

    class Parser {


        public:
            Parser(lexer::Lexer*);
            Node* Parse();
            ~Parser();

        private:

            bool check(lexer::LexemeType);
            void match(lexer::LexemeType);
            void matchType();
            void consume();

            // pending functions
            bool funcDefPending();
            bool blockDeclPending();
            bool assignPending();
            bool varDefPending();
            bool ifPending();
            bool loopPending();
            bool returnPending();
            bool statementPending();
            bool expressionPending();
            bool typePending();
            

            // BlockDecl is composed of a block type (var or const) and a list of variable and their values
            Node* parseBlockDecl();

            // FuncDef is represented as a list 
            Node* parsePackage();
            Node* parseImports();

            Node* parseFuncDef();
            Node* parseFormalParam();
            Node* parseFormalParameters();

            Node* parseBlock();
            Node* parseStatement();
            Node* parseAssignment();
            Node* parseVarDef();
            Node* parseIfStmt();
            Node* parseLoop();
            Node* parseReturn();
            Node* parseExpression();
            Node* parseTerm();
            Node* parseUnary();

            std::unique_ptr<lexer::Lexeme>  current;
            lexer::Lexer*   lex;

    };

}