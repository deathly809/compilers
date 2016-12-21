
#include <ast/BlockDefinitions.hpp>

#include <ast/Identifier.hpp>
#include <ast/Expressions/Expression.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <symtable/Attribute.hpp>
#include <symtable/SymbolTable.hpp>
#include <symtable/Scope.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

namespace ast {

    BlockDefinition::BlockDefinition(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {

        if(NextType(lex) == lexer::VAR) {
            variable = true;
            consumeLexemeType(lex,lexer::VAR);
        }  else {
            variable = false;
            consumeLexemeType(lex,lexer::CONST);
        }
        symtable::IdentifierKind kind = variable? symtable::Var:symtable::Const;
    
        consumeLexemeType(lex,lexer::O_PAREN);

        while(NextType(lex) != lexer::C_PAREN) {

            std::unique_ptr<lexer::Lexeme> name = lex.Next();
            auto tmpAttr = new symtable::VariableAttribute(name->GetValue(), name->GetFilename(), name->GetLine(), name->GetColumn(),kind,NilType);
            auto attr = std::shared_ptr<symtable::Attribute>(tmpAttr);
            lex.PushBack(name);
            table->Insert(attr);

            Identifier* id = new Identifier(lex, table);
            consumeLexemeType(lex,lexer::EQUAL);
            Expression* expr = new Expression(lex, table);

            tmpAttr->SetVariableType(expr->ResultType());

            vars.push_back({id,expr});
        }
        consumeLexemeType(lex,lexer::C_PAREN);
    }

    BlockDefinition::~BlockDefinition() {
        for( auto&& v : vars ) {
            delete v.id;
            delete v.expr;
        }
        vars.clear();
    }

    void BlockDefinition::Validate() const {
        for( auto&& v : vars ) {
            v.id->Validate();
            v.expr->Validate();
        }
    }

    std::unique_ptr<hardware::Register> BlockDefinition::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        for( auto&& v : vars ) {
            v.expr->GenerateCode(codeGen);
            
            std::shared_ptr<symtable::Attribute> attr = table->Locate(v.id->GetName());
            std::shared_ptr<symtable::VariableAttribute> vAttr = std::static_pointer_cast<symtable::VariableAttribute,symtable::Attribute>(attr);
            
            vAttr->SetRegister(hardware::Register::GetRegister());

            int scope = table->GetScopeIndex(v.id->GetName());
            int pos = table->GetPositionIndex(v.id->GetName());

            codeGen.StI(
                scope,
                pos
            );
            
        }
        return nullptr;
    }

    size_t BlockDefinition::VariablesDeclared() const {
        return vars.size();
    }

    std::ostream& BlockDefinition::Write(std::ostream & os) const {
        if(variable) {
            os << "var (" << std::endl;
        } else {
            os << "const (" << std::endl;
        }
        for(const auto & v : vars) {
            os << *v.id << " = " << *v.expr << std::endl;
        }
        return os << ")";
    }

}