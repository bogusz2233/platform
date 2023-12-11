#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "drivers.h"

namespace drivers
{
    
class EmptyDriver : public Driver{
    
};

class DummyDriver : public Driver
{
public:
   MOCK_METHOD(Result, ReadImpl, (const void *data, uint32_t size), (override)); 
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

    drivers::Result result = empty_driver.Read(nullptr, 2);
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
    EXPECT_CALL(dummy_driver, ReadImpl).Times(1);
    dummy_driver.Read(test_data, 2);
}

TEST(Drivers, ReadShouldPassDataAndSizeArgumentsToReadImplFunction){
    drivers::DummyDriver dummy_driver;
    uint8_t test_data[2]{};

    EXPECT_CALL(dummy_driver, ReadImpl(&test_data[0], 2)).Times(1);

    dummy_driver.Read(test_data, 2);

}

TEST(Drivers, ReadShouldReturnReadImplFunctionReturnValue){
    drivers::DummyDriver dummy_driver;
    uint8_t test_data[2]{};

    EXPECT_CALL(dummy_driver, ReadImpl(&test_data[0], 2)).WillOnce(::testing::Return(2));

    drivers::Result status = dummy_driver.Read(test_data, sizeof(test_data));

    EXPECT_EQ(std::get<uint32_t>(status) , sizeof(test_data));
}
