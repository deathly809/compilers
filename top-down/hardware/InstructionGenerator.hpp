
#ifndef INSTRUCTIONGENERATOR_HPP_
#define INSTRUCTIONGENERATOR_HPP_

#include <ostream>

namespace hardware {

    class InstructionGenerator {

        public:
            InstructionGenerator(std::ostream & out);
            void Add();
            void Sub();
            void Mult();
            void Div();
            void Mod();
            void And();
            void Or();
            void Neg();
            void Not();
            void Eq();
            void Ne();
            void Lt();
            void Gt();
            void Le();
            void Ge();
            void In();
            void Out();
            void NOp();
            void LdC(int a1);
            void LdA(int a1, int a2);
            void LdV(int a1, int a2);
            void LdI(int a1, int a2);
            void St(int a1, int a2);
            void StI(int a1, int a2);
            void Jmp(std::string label);
            void JmpF(std::string label);
            void JmpT(std::string label);
            void Init();
            void Halt();
            void Alloc(int a1);
            void Call(std::string);
            void Proc(int a1);
            void Ret(int a1);
            void Enter(int a1);
            void Exit(int a1);
            void Dup();
            void Pop();
            void StL();
            void Ind();
            void InCh();
            void OutCh();
            void OutStr(int a1);
            void AddLabel(std::string label);

            void WriteLabel(std::string);

            std::string GenerateLabel();

            private:
                std::ostream & out;
                int label;
    };
}

#endif