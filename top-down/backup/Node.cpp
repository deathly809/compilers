
#include <Node.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <map>



namespace parser {
       
    std::map<NodeType,std::string> nodeType2String = {
        {nPackage, "package"},
        {nImport, "import"},
        {nFuncDef, "funcDef"},
        {nVarDeclBlock, "varBlockDef"},
        {nIf, "If"},
        {nLoop, "loop"},
        {nFuncCall, "funcCall"},
        {nReturn, "return"},
        {nAssign, "assign"},
        {nVarDecl, "varDecl"},
        {nPlus, "plus"},
        {nMinus, "minus"},
        {nMul, "mul"},
        {nDiv, "div"},
        {nMod, "mod"},
        {nBang, "bang"},
        {nUndef, "undef"},
        {nGlue, "glue"}
    };

    const std::string& nodeTypeToString(NodeType type) {
        return nodeType2String[type];
    }

        Node::Node() : type(nUndef), lexeme(nullptr), left(nullptr), right(nullptr) {
            /* EMPTY */ 
        }
        
        Node::Node(std::unique_ptr<lexer::Lexeme> & lexeme) : type(nUndef), lexeme(std::move(lexeme)), left(nullptr), right(nullptr) {
            /* EMPTY */ 
        }

        Node::Node(NodeType type) : type(type), lexeme(nullptr), left(nullptr), right(nullptr) {
            /* EMPTY */ 
        }

        Node::Node(std::unique_ptr<lexer::Lexeme> & lexeme, NodeType type) : type(type), lexeme(std::move(lexeme)), left(nullptr), right(nullptr) {
            /* EMPTY */ 
        }

        Node::Node(Node* left, Node* right) : type(nUndef) ,lexeme(nullptr), left(left), right(right) {
            /* EMPTY */ 
        }

        Node::Node(Node* left, Node* right, NodeType type) : type(type) ,lexeme(nullptr), left(left), right(right) {
            /* EMPTY */ 
        }

        Node::Node(Node* left, Node* right, std::unique_ptr<lexer::Lexeme> & lexeme, NodeType type) : type(type) ,lexeme(std::move(lexeme)), left(left), right(right) {
            /* EMPTY */ 
        }

        // Deconstructors
        Node::~Node() {
            if(left != nullptr) {
                delete left;
                left = nullptr;
            }

            if(right != nullptr) {
                delete right;
                right = nullptr;
            }

            if(lexeme != nullptr) {
                lexeme = nullptr;
            }
        }

        // Getters

        Node* Node::GetLeft() const {
            return left;
        }

        Node* Node::GetRight() const {
            return left;
        }

        NodeType Node::GetType() const {
            return type;
        }

        const std::unique_ptr<lexer::Lexeme>& Node::GetLexeme() const {
            return lexeme;
        }

        // Setters

        void Node::SetLeft(Node* newLeft) {
            left = newLeft;
        }

        void Node::SetRight(Node* newRight) {
            right = newRight;
        }

        void Node::SetType(NodeType newType) {
            type = newType;
        }

        void Node::SetLexeme(std::unique_ptr<lexer::Lexeme> & newLexeme) {
            lexeme = std::move(newLexeme);
        }

        std::ostream& operator<<(std::ostream & out , const Node & n) {
            if(n.GetType() == parser::nUndef && n.GetLexeme() != nullptr) {
                out <<  *(n.GetLexeme());            
            } else {
                out << nodeTypeToString(n.GetType());
            }
            return out;
        }
}
