
#include <hardware/InstructionGenerator.hpp>

namespace hardware {

            InstructionGenerator::InstructionGenerator(std::ostream & out) : out(out){
                // empty
            }
            void InstructionGenerator::Add() {
                out << "\tADD" << std::endl;
            }

            void InstructionGenerator::Sub() {
                out << "\tSUB" << std::endl;
            }

            void InstructionGenerator::Mult() {
                out << "\tMULT" << std::endl;
            }
            
            void InstructionGenerator::Div() {
                out << "\tDIV" << std::endl;
            }
            
            void InstructionGenerator::Mod() {
                out << "\tMOD" << std::endl;
            }
            
            void InstructionGenerator::And() {
                out << "\tAND" << std::endl;
            }
            
            void InstructionGenerator::Or() {
                out << "\tOR" << std::endl;
            }
            
            void InstructionGenerator::Neg() {
                out << "\tNEG" << std::endl;
            }
            
            void InstructionGenerator::Not() {
                out << "\tNOT" << std::endl;
            }
            
            void InstructionGenerator::Eq() {
                out << "\tEQ" << std::endl;
            }
            
            void InstructionGenerator::Ne() {
                out << "\tNE" << std::endl;
            }
            
            void InstructionGenerator::Lt() {
                out << "\tLT" << std::endl;
            }
            
            void InstructionGenerator::Gt() {
                out << "\tGT" << std::endl;
            }
            
            void InstructionGenerator::Le() {
                out << "\tLE" << std::endl;
            }
            
            void InstructionGenerator::Ge() {
                out << "\tGE" << std::endl;
            }
            
            void InstructionGenerator::In() {
                out << "\tIN" << std::endl;
            }
            
            void InstructionGenerator::Out() {
                out << "\tOUT" << std::endl;
            }
            
            void InstructionGenerator::NOp() {
                out << "\tNOP" << std::endl;
            }
            
            void InstructionGenerator::LdC(int a1) {
                out << "\tLDC " << a1 << std::endl;
            }
            
            void InstructionGenerator::LdA(int a1, int a2) {
                out << "\tLDA " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::LdV(int a1, int a2) {
                out << "\tLDV " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::LdI(int a1, int a2) {
                out << "\tLDI " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::St(int a1, int a2) {
                out << "\tST " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::StI(int a1, int a2) {
                out << "\tSTI " << a1 << " " << a2 << std::endl;
            }
            
            void InstructionGenerator::JMP(int a1) {
                out << "\tJMP " << a1 << std::endl;
            }
            
            void InstructionGenerator::JMPF(int a1) {
                out << "\tJMPF " << a1 << std::endl;
            }
            
            void InstructionGenerator::JMPT(int a1) {
                out << "\tJMPT " << a1 << std::endl;
            }
            
            void InstructionGenerator::Init() {
                out << "\tINIT" << std::endl;
            }
            
            void InstructionGenerator::Halt() {
                out << "\tHALT" << std::endl;
            }
            
            void InstructionGenerator::Alloc(int a1) {
                out << "\tALLOC " << a1 << std::endl;
            }
            
            void InstructionGenerator::Call(int a1) {
                out << "\tCALL " << a1 << std::endl;
            }
            
            void InstructionGenerator::Proc(int a1) {
                out << "\tPROC " << a1 << std::endl;
            }
            
            void InstructionGenerator::Ret(int a1) {
                out << "\tRET " << a1 << std::endl;
            }
            
            void InstructionGenerator::Enter(int a1) {
                out << "\tENTER " << a1 << std::endl;
            }
            
            void InstructionGenerator::Exit(int a1) {
                out << "\tEXIT " << a1 << std::endl;
            }
            
            void InstructionGenerator::Dup() {
                out << "\tDUP" << std::endl;
            }
            
            void InstructionGenerator::Pop() {
                out << "\tPOP" << std::endl;
            }
            
            void InstructionGenerator::StL() {
                out << "\tSTL" << std::endl;
            }
            
            void InstructionGenerator::Ind() {
                out << "\tIND" << std::endl;
            }
            
            void InstructionGenerator::InCh() {
                out << "\tINCH" << std::endl;
            }
            
            void InstructionGenerator::OutCh() {
                out << "\\tOUTCH" << std::endl;
            }
            
            void InstructionGenerator::OutStr(int a1) {
                out << "\tOUTSTR ";
            }
            
            void InstructionGenerator::AddLabel(std::string label) {
                out << label << ":";
            }
            

    }
