
#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_


#include <ast/Type.hpp>
#include <string>

namespace symtable {

    
    enum AttributeType {IntAttributeType, RealAttributeType, StringAttributeType, BooleanAttributeType, NilAttributeType, VariableAttributeType, FunctionAttributeType };
    enum IdentifierKind { Const, Var };
    
    std::string& IdentifierKindToString(IdentifierKind idk);
    std::string& AttributeTypeToString(IdentifierKind idk);
    
    class Attribute {
        protected:
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

        private:
            AttributeType type;
            std::string name;

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
        private:
            IdentifierKind iKind;
            ast::ValueType iType;
        public:
            VariableAttribute(std::string name, IdentifierKind kind, ast::ValueType type);
            IdentifierKind GetKind();
            ast::ValueType GetVariableType();

            virtual void Write(std::ostream & os) const;

    };

    class FunctionAttribute : public Attribute {
        private:
            ast::ValueType iType;
        public:
            FunctionAttribute(std::string name, ast::ValueType type);
            ast::ValueType GetReturnType();

            virtual void Write(std::ostream & os) const;
    };

    std::ostream& operator<<(std::ostream & os, const Attribute & attr);

}


#endif