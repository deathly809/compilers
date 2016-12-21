
#include <ast/Identifier.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <symtable/SymbolTable.hpp>
#include <symtable/Attribute.hpp>
#include <symtable/Scope.hpp>

#include <iostream>

namespace ast {

        Identifier::Identifier(lexer::Lexer& lex, symtable::SymbolTable * table) : Ast(table), lexeme(lex.Next()) {
            checkLexemeType(lexeme,lexer::ID);
            lex.HasNext();
        }

        Identifier::~Identifier() {
        }

        void Identifier::Validate() const {
            scope = table->GetDeclaringScope(lexeme->GetValue());

            if(!scope) {
                throw std::runtime_error("use of an undeclared variable: " + lexeme->GetValue() + " on line " + std::to_string(lexeme->GetLine()));
            }
        }

        std::unique_ptr<hardware::Register> Identifier::GenerateCode(hardware::InstructionGenerator & codeGen) const {
            

            int scp = ScopeID();
            int idx = ScopePosition();
            if(idx != -1) {
                codeGen.LdV(
                    scp,
                    idx + 1
                );
            } else {
                throw std::runtime_error("unknown variable " + lexeme->GetValue());
            }

            return nullptr;
        }

        size_t Identifier::ScopeID() const {
            return scope->GetID();
        }

        size_t Identifier::ScopePosition() const {
            return scope->VariableIndex(lexeme->GetValue());
        }

        ValueType Identifier::ResultType() const {
            if(!scope) {
                return IntType;
            }

            auto attr = scope->GetVariableAttribute(GetName());
            if(!attr) {
                return IntType;
            }
            
            return attr->GetVariableType();
        }

        std::string Identifier::GetName() const {
            return lexeme->GetValue();
        }

        std::ostream& Identifier::Write(std::ostream & os) const {
            return os << GetName();
        }

        std::string Identifier::GetFilename() const {
            return lexeme->GetFilename();
        }

        int Identifier::GetLine() const {
            return lexeme->GetLine();
        }

        int Identifier::GetColumn() const {
            return lexeme->GetColumn();
        }

}