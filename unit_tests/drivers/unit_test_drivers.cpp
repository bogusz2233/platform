#include <gtest/gtest.h>

#include "drivers.h"

namespace drivers
{
    
class EmptyDriver : public Driver{
    
};

class DummyDriver : public Driver{
    public: 
        struct ReadPassedArgumments
        {
            const void *data; 
            uint32_t size;
        } read_passed_arrguments;

       bool ReadFunctionCalled(){
            return read_function_called;
        }

    private:
        bool read_function_called = false;

        Result ReadImpl(const void *data, uint32_t size) override{
            read_function_called = true;
            read_passed_arrguments.data = data;
            read_passed_arrguments.size = size;
            
            return size;
        }
     
};

} // namespace drivers

TEST(Drivers, ReadShouldReturnNotImplemented) {
  drivers::EmptyDriver empty_driver;

  // Expect equality.
  uint8_t test_data[2]{};

  drivers::Result result = empty_driver.Read(test_data, sizeof(test_data));
  
  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::NOT_IMPLEMENTED);
}

TEST(Drivers, ReadShouldReturnNULLPTRStatusIfNullptrPassed){
  drivers::EmptyDriver empty_driver;

   drivers::Result result =empty_driver.Read(nullptr, 2);
    EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::NULLPTR);
}

TEST(Drivers, ReadShouldReturnInvalidArgumentIf0Passed){
  drivers::EmptyDriver empty_driver;
  uint8_t test_data[2]{};

   drivers::Result result = empty_driver.Read(test_data, 0);

    EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::INVALID_ARGUMENT);
}

TEST(Drivers, ReadShouldCallReadImplFunction){
  drivers::DummyDriver dummy_driver;
  uint8_t test_data[2]{};
    dummy_driver.Read(test_data, 2);

    EXPECT_EQ(dummy_driver.ReadFunctionCalled(), true);
}

TEST(Drivers, ReadShouldPassDataArgumentToReadImplFunction){
    drivers::DummyDriver dummy_driver;
    uint8_t test_data[2]{};
    dummy_driver.Read(test_data, 2);

    EXPECT_EQ(dummy_driver.read_passed_arrguments.data , test_data);
}

TEST(Drivers, ReadShouldPassSizeArgumentToReadImplFunction){
    drivers::DummyDriver dummy_driver;
    uint8_t test_data[2]{};
    dummy_driver.Read(test_data, sizeof(test_data));

    EXPECT_EQ(dummy_driver.read_passed_arrguments.size , sizeof(test_data));
}

TEST(Drivers, ReadShouldReturnReadImplFunctionReturnValue){
    drivers::DummyDriver dummy_driver;
    uint8_t test_data[2]{};
    drivers::Result status = dummy_driver.Read(test_data, sizeof(test_data));

    EXPECT_EQ(std::get<uint32_t>(status) , sizeof(test_data));

}
