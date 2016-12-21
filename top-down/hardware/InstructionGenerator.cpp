
#include <hardware/InstructionGenerator.hpp>

namespace hardware {

            InstructionGenerator::InstructionGenerator(std::ostream & out) : out(out), label(0){
                // empty
            }
            void InstructionGenerator::Add() {
                out << "\t\tADD" << std::endl;
            }

            void InstructionGenerator::Sub() {
                out << "\t\tSUB" << std::endl;
            }

            void InstructionGenerator::Mult() {
                out << "\t\tMULT" << std::endl;
            }
            
            void InstructionGenerator::Div() {
                out << "\t\tDIV" << std::endl;
            }
            
            void InstructionGenerator::Mod() {
                out << "\t\tMOD" << std::endl;
            }
            
            void InstructionGenerator::And() {
                out << "\t\tAND" << std::endl;
            }
            
            void InstructionGenerator::Or() {
                out << "\t\tOR" << std::endl;
            }
            
            void InstructionGenerator::Neg() {
                out << "\t\tNEG" << std::endl;
            }
            
            void InstructionGenerator::Not() {
                out << "\t\tNOT" << std::endl;
            }
            
            void InstructionGenerator::Eq() {
                out << "\t\tEQ" << std::endl;
            }
            
            void InstructionGenerator::Ne() {
                out << "\t\tNE" << std::endl;
            }
            
            void InstructionGenerator::Lt() {
                out << "\t\tLT" << std::endl;
            }
            
            void InstructionGenerator::Gt() {
                out << "\t\tGT" << std::endl;
            }
            
            void InstructionGenerator::Le() {
                out << "\t\tLE" << std::endl;
            }
            
            void InstructionGenerator::Ge() {
                out << "\t\tGE" << std::endl;
            }
            
            void InstructionGenerator::In() {
                out << "\t\tIN" << std::endl;
            }
            
            void InstructionGenerator::Out() {
                out << "\t\tOUT" << std::endl;
            }
            
            void InstructionGenerator::NOp() {
                out << "\t\tNOP" << std::endl;
            }
            
            void InstructionGenerator::LdC(int a1) {
                out << "\t\tLDC " << a1 << std::endl;
            }
            
            void InstructionGenerator::LdA(int a1, int a2) {
                out << "\t\tLDA " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::LdV(int a1, int a2) {
                out << "\t\tLDV " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::LdI(int a1, int a2) {
                out << "\t\tLDI " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::St(int a1, int a2) {
                out << "\t\tST " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::StI(int a1, int a2) {
                out << "\t\tSTI " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::Jmp(std::string lbl) {
                out << "\t\tJMP " << lbl << std::endl;
            }
            
            void InstructionGenerator::JmpF(std::string lbl) {
                out << "\t\tJMPF " << lbl << std::endl;
            }
            
            void InstructionGenerator::JmpT(std::string lbl) {
                out << "\t\tJMPT " << lbl << std::endl;
            }
            
            void InstructionGenerator::Init() {
                out << "\t\tINIT" << std::endl;
            }
            
            void InstructionGenerator::Halt() {
                out << "\t\tHALT" << std::endl;
            }
            
            void InstructionGenerator::Alloc(int a1) {
                out << "\t\tALLOC " << a1 << std::endl;
            }
            
            void InstructionGenerator::Call(std::string label) {
                out << "\t\tCALL " << label << std::endl;
            }
            
            void InstructionGenerator::Proc(int a1) {
                out << "\t\tPROC " << a1 << std::endl;
            }
            
            void InstructionGenerator::Ret(int a1) {
                out << "\t\tRET " << a1 << std::endl;
            }
            
            void InstructionGenerator::Enter(int a1) {
                out << "\t\tENTER " << a1 << std::endl;
            }
            
            void InstructionGenerator::Exit(int a1) {
                out << "\t\tEXIT " << a1 << std::endl;
            }
            
            void InstructionGenerator::Dup() {
                out << "\t\tDUP" << std::endl;
            }
            
            void InstructionGenerator::Pop() {
                out << "\t\tPOP" << std::endl;
            }
            
            void InstructionGenerator::StL() {
                out << "\t\tSTL" << std::endl;
            }
            
            void InstructionGenerator::Ind() {
                out << "\t\tIND" << std::endl;
            }
            
            void InstructionGenerator::InCh() {
                out << "\t\tINCH" << std::endl;
            }
            
            void InstructionGenerator::OutCh() {
                out << "\t\tOUTCH" << std::endl;
            }
            
            void InstructionGenerator::OutStr(int a1) {
                out << "\t\tOUTSTR ";
            }
            
            void InstructionGenerator::AddLabel(std::string label) {
                out << label << ":";
            }

            void InstructionGenerator::WriteLabel(std::string theLabel) {
                out << theLabel;
            }

            std::string InstructionGenerator::GenerateLabel() {
                return "L" + std::to_string(++label);
            }

    }
