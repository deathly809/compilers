
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
        kind = variable? symtable::Var:symtable::Const;
    
        consumeLexemeType(lex,lexer::O_PAREN);

        while(NextType(lex) != lexer::C_PAREN) {
            Identifier* id = new Identifier(lex, table);
            consumeLexemeType(lex,lexer::EQUAL);
            Expression* expr = new Expression(lex, table);

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

            auto attr = std::shared_ptr<symtable::Attribute>(new symtable::VariableAttribute(v.id->GetName(), v.id->GetFilename(), v.id->GetLine(), v.id->GetColumn(),kind,v.expr->ResultType()));
            table->Insert(attr);

            v.id->Validate();
            v.expr->Validate();

        }
    }

    std::unique_ptr<hardware::Register> BlockDefinition::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        for( auto&& v : vars ) {
            v.expr->GenerateCode(codeGen);
            
            std::shared_ptr<symtable::Attribute> attr = table->Locate(v.id->GetName());
            std::shared_ptr<symtable::VariableAttribute> vAttr = std::static_pointer_cast<symtable::VariableAttribute,symtable::Attribute>(attr);

            int scope = table->GetScopeIndex(v.id->GetName());
            int pos = table->GetPositionIndex(v.id->GetName());

            codeGen.St(
                scope,
                pos + 1
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