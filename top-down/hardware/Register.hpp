
#ifndef REGISTER_HPP_
#define REGISTER_HPP_

#include <vector>
#include <memory>

namespace hardware {

    class Register {

        protected:

            static std::vector<size_t> claimedRegisters;
            static std::vector<size_t> unclaimedRegisters;
            static size_t maxNumRegisters;

            size_t id;

            Register(size_t id);

        public:
            ~Register();

            size_t GetID() const;

            static std::unique_ptr<Register> GetRegister();
            
    };

}

#endif