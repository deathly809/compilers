
#include <Parser.hpp>

#include <Lexer.hpp>
#include <Lexeme.hpp>

#include <Node.hpp>

#include <exception>
#include <sstream>
#include <map>

#include <iostream>

namespace parser {

    char errBuff[512];


    void print(std::string msg) {
        std::cout << msg <<std::endl;
    }

    Parser::Parser(lexer::Lexer *lex) : lex(lex) {
        /* Empty */
    }

    void Parser::consume() {
        lex->HasNext();
        current = lex->Next();
    }

    bool Parser::check(lexer::LexemeType t) {
        return current->GetType() == t; 
    }

    void Parser::matchType() {
        if(check(lexer::INT)) {
            match(lexer::INT);
        } else if(check(lexer::STRING)) {
            match(lexer::STRING);
        } else if(check(lexer::REAL)) {
            match(lexer::REAL);
        } else {
            throw std::runtime_error("Unknown TYPE");
        }
    }

    void Parser::match(lexer::LexemeType t) { 
        if(!check(t)) {
            if(current == nullptr) {
                current = std::move(std::unique_ptr<lexer::Lexeme>(new lexer::Lexeme(lexer::UNDEF,"NULLPTR","",0,0)));
            }
            std::stringstream ss;
            ss << "in file ";
            ss << current->GetFileName();
            ss << " on line "; 
            ss << current->GetLine();
            ss << ", column ";
            ss << current->GetColumn();
            ss << " expected type ";
            ss << LexemeTypeToString(t);
            ss << " but found ";
            ss << LexemeTypeToString(current->GetType()); 
            throw std::runtime_error(ss.str());
        }
        consume();
    }


    std::string unexpectedToken(std::unique_ptr<lexer::Lexeme> & current) {
        std::stringstream ss;
        ss << "in file" << current->GetFileName() << " on line " << current->GetLine() << " column " << current->GetColumn();
        ss << " unexpected token: ";
        if(current->GetValue() == "") {
            ss << LexemeTypeToString(current->GetType());
        } else {
            ss << current->GetValue();
        }
        return ss.str();
    }

    // pending functions
    bool Parser::funcDefPending() {
        return check(lexer::FUNC);
    }
    bool Parser::blockDeclPending() {
        return check(lexer::O_BRACE);
    }
    bool Parser::assignPending() {
        return check(lexer::ID);
    }
    bool Parser::varDefPending() {
        return check(lexer::ID) || check(lexer::VAR);
    }
    bool Parser::ifPending() {
        return check(lexer::IF);
    }
    bool Parser::loopPending() {
        return check(lexer::LOOP);
    }
    bool Parser::returnPending() {
        return check(lexer::RETURN);
    }
    bool Parser::statementPending() {
        return check(lexer::ID) || loopPending() || ifPending() || returnPending();
    }
    bool Parser::expressionPending() {
        return check(lexer::INT) || check(lexer::REAL) || check(lexer::STRING) || check(lexer::ID) || check(lexer::BANG);
    }

    bool Parser::typePending() {
        return check(lexer::INT) || check(lexer::REAL) || check(lexer::STRING);
    }

    Node* Parser::Parse() {
        consume();
        
        Node* left = parsePackage();
        Node* right = new Node(parseImports(), nullptr ,nGlue);
        
        Node* result = new Node(left,right,nGlue);

        Node* curr = right;

        while(current != nullptr) {
            
            curr->SetRight(new Node(nGlue));
            curr = curr->GetRight();

            if(funcDefPending()) {
                curr->SetLeft(parseFuncDef());
            } else if(blockDeclPending()) {
                curr->SetLeft(parseBlockDecl());
            } else {
                throw std::runtime_error("derp" + unexpectedToken(current));
            }

        }
        return result;
    }


    // package ID
    Node* Parser::parsePackage() {
        match(lexer::PACKAGE);
        Node* result = new Node(current,nPackage);
        match(lexer::ID);
        return result;
    }

    //  epsilon | ( import ( STRING | "(" STRING { STRING } ")" ) )
    Node* Parser::parseImports() {
        Node* result = nullptr;
        if(check(lexer::IMPORT)) {
            match(lexer::IMPORT);
            if(check(lexer::O_PAREN)) {
                consume();
                result = new Node(current,nImport);

                Node* curr = result;
                consume();
                while(!check(lexer::C_PAREN)) {
                    curr->SetRight(new Node(current,nImport));
                    match(lexer::STRING);
                    curr = curr->GetRight();
                }
                match(lexer::C_PAREN);
            } else {
                result = new Node(current,nImport);
                match(lexer::STRING);
            }
        }
        return result;
    }

    // ("const" | "var" ) "(" ID = EXPR [ , ID = EXPR ] ")"
    Node* Parser::parseBlockDecl() {
        Node* result = new Node(current,nVarDeclBlock);
        
        if(check(lexer::VAR)) {
            match(lexer::VAR);
        } else if(check(lexer::CONST)) {
            match(lexer::CONST);
        } else {
            throw std::runtime_error(unexpectedToken(current));
        }

        match(lexer::O_PAREN);
        result->SetRight(new Node(parseAssignment(),nullptr));
        Node* curr = result->GetRight();
        while(check(lexer::COMMA)) {
            curr->SetRight(new Node(parseAssignment(),nullptr));
            curr = curr->GetRight();
        }
        match(lexer::C_PAREN);

        return result;
    }


    // ID TYPE
    Node* Parser::parseFormalParam() {

        Node* left = new Node(nullptr,nullptr,current,nGlue);
        match(lexer::ID);

        Node* right = new Node(nullptr,nullptr,current,nGlue);
        matchType();

        return new Node(left,right, nGlue);
    }


    // ([name] ([return type]) ((id,type) (id,type) (id,type)) body)
    // FuncDef is represented as a list 
    Node* Parser::parseFuncDef() {
        match(lexer::FUNC);

        std::unique_ptr<lexer::Lexeme> resultType = nullptr;
        
        // name of function
        Node* name = new Node(current);
        match(lexer::ID);

        // formal parameters
        Node* formParams = parseFormalParameters();
        
        // return type
        if(typePending()) {
            resultType = std::move(current);
            matchType();
        }

        Node* block = parseBlock();

        // (cons name (cons formParam body))
        return new Node(name,new Node(formParams,block),resultType,nFuncDef);
    }

    Node* Parser::parseFormalParameters() {
        Node* result = nullptr;

        match(lexer::O_PAREN);

        if(!check(lexer::C_PAREN)) {
            Node* result = new Node(parseFormalParam(),nullptr);
            Node* curr = result;
            
            while(!check(lexer::C_PAREN)) {
                match(lexer::COMMA);
                curr->SetRight(new Node(parseFormalParam(),nullptr));
                curr = curr->GetRight();
            }
        }

        match(lexer::C_PAREN);
        return result;
    }

    Node* Parser::parseBlock() {
        match(lexer::O_BRACE);
        Node* result = new Node();
        Node* curr = result;

        while( !check(lexer::C_BRACE)) {
            curr->SetRight(new Node(parseStatement(),nullptr));
            curr = curr->GetRight();
            
        }
        match(lexer::C_BRACE);
        return result;
    }

    // parseStmt = IFStmt | LoopStmt | ID ( ( "=" | "=" ) EXPR | "(" [ EXPR { "," EXPR } ] ")" )
    Node* Parser::parseStatement() {
        Node* stmt;
        if(loopPending()) {
            stmt = parseLoop();
        } else if(ifPending()) {
            stmt = parseIfStmt();
        } else if(returnPending()) {
            stmt = parseReturn();
        } else if(check(lexer::ID)) {  // ID = EXPR | ID = EXPR | ID([EXPR {, EXPR}])
            stmt = new Node(current);
            match(lexer::ID);
            if(check(lexer::EQUAL)) {              // assigment
                consume();
                stmt->SetType(nAssign);
                stmt->SetRight(parseExpression());
            } else if(check(lexer::EQUAL)) {     // var declaration
                consume();
                stmt->SetType(nVarDecl);
                stmt->SetRight(parseExpression());
            } else if(check(lexer::O_PAREN)) {
                consume();
                stmt->SetType(nFuncCall);
                if(!check(lexer::C_PAREN)) {
                    stmt->SetRight(parseExpression());
                    Node* curr = stmt->GetRight();
                    while(check(lexer::COMMA)) {
                        consume();
                        stmt->SetRight(parseExpression());
                        curr = curr->GetRight();
                    }
                }
                match(lexer::C_PAREN);
            }
        } else if(check(lexer::VAR)) {
            consume();
            stmt = new Node(current, nVarDecl);
            match(lexer::ID);

            stmt->SetLeft(new Node(current));
            matchType();

        } else {
            throw std::runtime_error(unexpectedToken(current));
        }
        return stmt;
    }
    Node* Parser::parseAssignment() {
        Node* result = new Node(new Node(current),nullptr);
        match(lexer::ID);
        match(lexer::EQUAL);
        result->SetRight(parseExpression());
        return result;
    }
    Node* Parser::parseVarDef() {
        return nullptr;
    }

    Node* Parser::parseIfStmt() {
        match(lexer::IF);

        Node* condition = parseExpression();
        Node* blocks = new Node(parseBlock(),nullptr);
        
        match(lexer::C_BRACE);
        if(check(lexer::ELSE)) {
            match(lexer::ELSE);
            blocks->SetRight(parseBlock());
        }
        return new Node(condition,blocks);
    }

    // Apparently only INIT ; TEST ; INC 
    Node* Parser::parseLoop() {

        match(lexer::LOOP);
        Node* init = parseExpression();

        match(lexer::SEMI);
        Node* test = parseExpression();

        match(lexer::SEMI);
        Node* update = parseExpression();

        Node* initTestUpdate = new Node(init, new Node(test, update));
        Node* block = parseBlock();

        return new Node(initTestUpdate, block,nLoop);
    }
    Node* Parser::parseReturn() {
        match(lexer::RETURN);
        return new Node(parseExpression(),nullptr,nReturn);
    }

    // EXPR = LTWO ( + | - )  
    Node* Parser::parseExpression() {
        Node* result = parseTerm();

        if(check(lexer::PLUS) || check(lexer::MINUS)) {
            result = new Node(result,parseExpression());
            if(check(lexer::PLUS)) {
                result->SetType(nPlus);
            } else {
                result->SetType(nMinus);
            }
        }
        return result;
    }

    Node* Parser::parseTerm() {
        Node* result = parseUnary();

        if(check(lexer::MUL) || check(lexer::DIV) || check(lexer::MOD)) {
            result = new Node(result, parseTerm());
            if(check(lexer::MUL)) {
                result->SetType(nMul);
            } else if(check(lexer::DIV)) {
                result->SetType(nDiv);
            } else {
                result->SetType(nMod);
            }
        }
        return result;
    }

    // 
    Node* Parser::parseUnary() {
        Node *result = new Node();
        Node* curr = result;

        // Get all the bangs
        bool bangs = true;
        while(check(lexer::BANG)) {
            bangs = !bangs;
        }

        if(!bangs) {
            curr->SetType(nBang);
            curr->SetRight(new Node());
            curr = curr->GetRight();
        }

        switch(current->GetType()) {
            case lexer::STRING:
                curr->SetLexeme(current);
                consume();
                break;
            case lexer::ID:
                match(lexer::ID);
                if(check(lexer::O_PAREN)) {
                    match(lexer::O_PAREN);

                } else {
                    curr->SetLexeme(current);
                    consume();
                }
                break;
            case lexer::O_PAREN:
                match(lexer::O_PAREN);
                curr->SetRight(parseExpression());
                match(lexer::C_PAREN);
                break;
            default:
                throw std::runtime_error("check this");
            }
        return result;
    }

}