
#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include <ast/Type.hpp>
#include <hardware/Register.hpp>

#include <string>
#include <memory>

namespace symtable {

    enum AttributeType {IntAttributeType, RealAttributeType, StringAttributeType, BooleanAttributeType, NilAttributeType, VariableAttributeType, FunctionAttributeType };
    enum IdentifierKind { Const, Var };
    
    std::string& IdentifierKindToString(IdentifierKind idk);
    std::string& AttributeTypeToString(IdentifierKind idk);
    
    class Attribute {
        protected:
            Attribute(std::string name, std::string filename, int line, int column, AttributeType type);
            Attribute(std::string name, AttributeType type);
        public:
            Attribute(const Attribute &) = delete;
            Attribute(const Attribute &&) = delete;
            Attribute& operator=(const Attribute &) = delete;
            Attribute& operator=(const Attribute &&) = delete;

            Attribute();
            ~Attribute();

            std::string GetName() const;
            AttributeType GetType() const;

            virtual void Write(std::ostream & os) const ;

            std::string GetFilename() {
                return filename;
            }

            int GetLine() {
                return line;
            }

            int GetColumn() {
                return column;
            }

        private:
            AttributeType type;

            std::string name;
            std::string filename;
            int line;
            int column;

    };

    class IntAttribute : public Attribute {
        private:
            int value;
        public:
            IntAttribute(std::string name, int value);
            int GetValue() const;

            virtual void Write(std::ostream & os) const ;

    };

    class RealAttribute : public Attribute {
        private:
            double value;
        public:

            RealAttribute(std::string name, double value);
            double GetValue() const;

            virtual void Write(std::ostream & os) const ;
            
    };

    class StringAttribute : public Attribute {
        private: 
                std::string value;
        public:

            StringAttribute(std::string name, std::string value);
            std::string GetValue() const;

            virtual void Write(std::ostream & os) const ;

    };

    class BooleanAttribute : public Attribute {
        private:
            bool value;

        public:
            BooleanAttribute(std::string name, bool value);
            bool GetValue() const;

            virtual void Write(std::ostream & os) const ;

    };

    class NilAttribute : public Attribute {
        public:
            NilAttribute();

            virtual void Write(std::ostream & os) const ;

    };

    /* Holds information about attributes */
    class VariableAttribute : public Attribute {

        public:
            VariableAttribute(std::string name, std::string filename, int line, int column, IdentifierKind kind, ast::ValueType type,int size = 1);
            IdentifierKind GetKind() const;
            ast::ValueType GetVariableType() const;

            int GetSize() const;
            void SetSize(int);

            void SetVariableType(ast::ValueType type);

            virtual void Write(std::ostream & os) const;
            void SetRegister(std::unique_ptr<hardware::Register> reg);

        private:
            int size;
            IdentifierKind iKind;
            ast::ValueType iType;
            std::unique_ptr<hardware::Register> reg;

    };

    class FunctionAttribute : public Attribute {

        public:
            FunctionAttribute(std::string name, std::string filename, int line, int column, ast::ValueType type);
            FunctionAttribute(std::function<void(hardware::InstructionGenerator&)> gen, std::string name, ast::ValueType type);

            ast::ValueType GetReturnType() const;
            void SetReturnType(ast::ValueType type);

            virtual void Write(std::ostream & os) const;
            std::string GetLabel() const;
            void SetLabel(std::string);

            bool IsBuiltIn();
            void GenerateCode(hardware::InstructionGenerator & codeGen) const;

        private:
            ast::ValueType iType;
            std::string label;
            bool builtin;
            std::function<void(hardware::InstructionGenerator&)> gen;

    };

    std::ostream& operator<<(std::ostream & os, const Attribute & attr);

}


#endif