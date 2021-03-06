
#ifndef IDENTIFIER_HPP_
#define IDENTIFIER_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

#include <memory>

namespace symtable {
    class Scope;
}

namespace hardware {
    class InstructionGenerator;
}

namespace lexer {
    class Lexeme;
}

namespace ast {

    class Identifier : public Ast {
        public:
            Identifier(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~Identifier();
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;
            std::string GetName() const;

            std::string GetFilename() const;
            int GetColumn() const;
            int GetLine() const;

            size_t ScopeID() const;
            size_t ScopePosition() const;
            
            
        private:
            std::unique_ptr<lexer::Lexeme> lexeme;
            mutable std::shared_ptr<symtable::Scope> scope;
    };

}

#endif
