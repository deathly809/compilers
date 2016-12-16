
#include <hardware/Register.hpp>

#include <algorithm>

namespace hardware {

    size_t Register::maxNumRegisters = 100;
    std::vector<size_t> Register::unclaimedRegisters;
    std::vector<size_t> Register::claimedRegisters;

    Register::Register(size_t id) : id(id) {
        /* Empty */
    }

    Register::~Register() {
        auto ptr = std::find(claimedRegisters.begin(),claimedRegisters.end(),id);
        std::swap(*ptr,claimedRegisters.back());
        claimedRegisters.pop_back();
        unclaimedRegisters.push_back(id);        
    }

    size_t Register::GetID() const {
        return this->id;
    }

    std::unique_ptr<Register> Register::GetRegister() {
        // Init
        if(claimedRegisters.size() == 0 && unclaimedRegisters.size() == 0) {
            for(size_t i = 0 ; i < maxNumRegisters; ++i) {
                Register::unclaimedRegisters.push_back(maxNumRegisters - i - 1);
            }
        }

        if(unclaimedRegisters.size() == 0) {
            throw std::runtime_error("all registers in use");
        }

        size_t id = unclaimedRegisters.back();
        unclaimedRegisters.pop_back();
        claimedRegisters.push_back(id);

        return std::unique_ptr<Register>(new Register(id));
    }

}