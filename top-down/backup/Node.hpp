
#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <memory>

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
            Node(std::unique_ptr<lexer::Lexeme> & lexeme);
            Node(NodeType type);
            Node(std::unique_ptr<lexer::Lexeme> & lexeme, NodeType type);
            Node(Node* left, Node* right, std::unique_ptr<lexer::Lexeme> & lexeme, NodeType type);
            Node(Node* left, Node* right, NodeType type);
            Node(Node* left, Node* right);
            ~Node();

            NodeType GetType() const;
            Node* GetLeft() const;
            Node* GetRight() const;
            const std::unique_ptr<lexer::Lexeme>& GetLexeme() const;

            void SetLeft(Node* node);
            void SetRight(Node* node);
            void SetType(NodeType type);
            void SetLexeme(std::unique_ptr<lexer::Lexeme> & l);

        private:
            NodeType type;
            std::unique_ptr<lexer::Lexeme> lexeme;
            Node* left, *right;

    };

    std::ostream& operator<<(std::ostream & out , const Node & n);

}

#endif