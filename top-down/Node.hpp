
#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>

namespace lexer {
    class Lexeme;
}

namespace parser {

    enum NodeType { nPackage , nImport , nFuncDef, 
                    nIf , nFuncCall, nLoop, nReturn,
                    nAssign, nVarDecl , nVarDeclBlock,
                    nPlus, nMinus, nMul, nDiv, nMod, nBang,
                    nUndef , nGlue
    };

    const std::string& nodeTypeToString(NodeType);

    class Node {

        public:
            Node();
            Node(lexer::Lexeme* lexeme);
            Node(NodeType type);
            Node(lexer::Lexeme* lexeme, NodeType type);
            Node(Node* left, Node* right, lexer::Lexeme *lexeme, NodeType type);
            Node(Node* left, Node* right);
            ~Node();

            NodeType GetType() const;
            Node* GetLeft() const;
            Node* GetRight() const;
            const lexer::Lexeme* GetLexeme() const;

            void SetLeft(Node* node);
            void SetRight(Node* node);
            void SetType(NodeType type);
            void SetLexeme(lexer::Lexeme* l);

        private:
            NodeType type;
            lexer::Lexeme *lexeme;
            Node* left, *right;

    };

    std::ostream& operator<<(std::ostream & out , const Node & n);

}

#endif