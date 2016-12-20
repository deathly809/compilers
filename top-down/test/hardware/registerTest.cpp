
#include <test/catch.hpp>

#include <hardware/Register.hpp>
#include <hardware/InstructionGenerator.hpp>

#include <vector>
#include <memory>

TEST_CASE("Register: grab and release","[Regsiter]") {
    SECTION("grab one at a time") {
        for(int i = 0; i < 100; ++i) {
            auto r = hardware::Register::GetRegister();
            REQUIRE(r->GetID() == 0);
        }
    }
    SECTION("grab five at a time") {
        bool test[5];

        for(int i = 0; i < 100; ++i) {
            std::fill(test,test+5,false);

            auto r1 = hardware::Register::GetRegister();
            auto r2 = hardware::Register::GetRegister();
            auto r3 = hardware::Register::GetRegister();
            auto r4 = hardware::Register::GetRegister();
            auto r5 = hardware::Register::GetRegister();

            REQUIRE(r1->GetID() <= 4);
            REQUIRE(r1->GetID() >= 0);

            REQUIRE(r2->GetID() <= 4);
            REQUIRE(r2->GetID() >= 0);
            
            REQUIRE(r3->GetID() <= 4);
            REQUIRE(r3->GetID() >= 0);
            
            REQUIRE(r4->GetID() <= 4);
            REQUIRE(r4->GetID() >= 0);
            
            REQUIRE(r5->GetID() <= 4);
            REQUIRE(r5->GetID() >= 0);

            test[r1->GetID()] = true;
            test[r2->GetID()] = true;
            test[r3->GetID()] = true;
            test[r4->GetID()] = true;
            test[r5->GetID()] = true;

            for(int i = 0 ; i < 5; ++i) REQUIRE(test[i]);

        }        
    }

    SECTION("grab all registers") {
        std::vector< std::unique_ptr< hardware::Register > > saved;
        for(int i = 0; i < 5; ++i) {
            for(int t = 0; t < 100; ++t) {
                REQUIRE_NOTHROW(saved.push_back(std::move(hardware::Register::GetRegister())));
            }
            REQUIRE_THROWS(hardware::Register::GetRegister());
            saved.clear();
        }
    }
}

