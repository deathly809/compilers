
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

        Identifier::Identifier(lexer::Lexer& lex, symtable::SymbolTable * table) : Ast(table), lexeme(lex.Next()), scope(table->GetDeclaringScope(lexeme->GetValue())), index(table->ScopeCount()) {
            checkLexemeType(lexeme,lexer::ID);
            lex.HasNext();
        }

        Identifier::~Identifier() {
        }

        void Identifier::Validate() const {
            /* Nothing to validate */
        }

        std::unique_ptr<hardware::Register> Identifier::GenerateCode(hardware::InstructionGenerator & codeGen) const {
            int idx = scope->VariableIndex(lexeme->GetValue());
            if(idx != -1) {
                codeGen.LdV(
                    index,
                    idx
                );
            } else {
                throw std::runtime_error("unknown variable " + lexeme->GetValue());
            }

            return nullptr;
        }

        ValueType Identifier::ResultType() const {
            return IntType;
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