
#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include <string>

namespace symtable {

    enum AttributeType {IntAttributeType, RealAttributeType, StringAttributeType, BooleanAttributeType, NilAttributeType, VariableAttributeType };
    enum IdentifierKind { Const, Var };
    enum IdentifierType { IntegerType, StringType, ArrayType, RealType, BooleanType, None };


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

            virtual std::string GetName();
            virtual AttributeType GetType();

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

    };

    class RealAttribute : public Attribute {
        private:
            double value;
        public:

            RealAttribute(std::string name, double value);
            double GetValue() const;
            
    };

    class StringAttribute : public Attribute {
        private: 
                std::string value;
        public:

            StringAttribute(std::string name, std::string value);
            std::string GetValue() const;
    };

    class BooleanAttribute : public Attribute {
        private:
            bool value;

        public:
            BooleanAttribute(std::string name, bool value);
            bool GetValue() const;
    };

    class NilAttribute : public Attribute {
        public:
            NilAttribute();
    };

    /* Holds information about attributes */
    class VariableAttribute : public Attribute {
        private:
            IdentifierKind iKind;
            IdentifierType iType;
        public:
            VariableAttribute(std::string name, IdentifierKind kind, IdentifierType type);
            IdentifierKind GetKind();
            IdentifierType GetVariableType();
    };

}

#endif