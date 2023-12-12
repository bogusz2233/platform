#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "drivers.h"

namespace drivers {

class EmptyDriver : public Driver {};

class DummyDriver : public Driver {
public:
  MOCK_METHOD(Result, ReadImpl, (void *data, uint32_t size), (override));
  MOCK_METHOD(Result, WriteImpl, (const void *data, uint32_t size), (override));
};

} // namespace drivers

TEST(Drivers, ReadShouldReturnNotImplemented) {
  drivers::EmptyDriver empty_driver;

  // Expect equality.
  uint8_t test_data[2]{};

  drivers::Result result = empty_driver.Read(test_data, sizeof(test_data));

  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::NOT_IMPLEMENTED);
}

TEST(Drivers, ReadShouldReturnNULLPTRStatusIfNullptrPassed) {
  drivers::EmptyDriver empty_driver;

  drivers::Result result = empty_driver.Read(nullptr, 2);
  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::NULLPTR);
}

TEST(Drivers, ReadShouldReturnInvalidArgumentIf0Passed) {
  drivers::EmptyDriver empty_driver;
  uint8_t              test_data[2]{};

  drivers::Result result = empty_driver.Read(test_data, 0);

  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::INVALID_ARGUMENT);
}

TEST(Drivers, ReadShouldCallReadImplFunction) {
  drivers::DummyDriver dummy_driver;
  uint8_t              test_data[2]{};
  EXPECT_CALL(dummy_driver, ReadImpl).Times(1);
  dummy_driver.Read(test_data, 2);
}

TEST(Drivers, ReadShouldPassDataAndSizeArgumentsToReadImplFunction) {
  drivers::DummyDriver dummy_driver;
  uint8_t              test_data[2]{};

  EXPECT_CALL(dummy_driver, ReadImpl(&test_data[0], 2)).Times(1);

  dummy_driver.Read(test_data, 2);
}

TEST(Drivers, ReadShouldReturnReadImplFunctionReturnValue) {
  drivers::DummyDriver         dummy_driver;
  uint8_t                      test_data[2]{};
  static const drivers::Result EXPECTED_RESULT = 2u;

  ON_CALL(dummy_driver, ReadImpl).WillByDefault(::testing::Return(EXPECTED_RESULT));
  drivers::Result status = dummy_driver.Read(test_data, sizeof(test_data));

  EXPECT_EQ(status, EXPECTED_RESULT);
}

TEST(Drivers, WriteShouldReturnNullptrIfNullptrPassed) {
  drivers::EmptyDriver empty_driver;

  drivers::Result result = empty_driver.Write(nullptr, 2);
  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::NULLPTR);
}

TEST(Drivers, WriteShouldReturnInvalidArgumentIf0SizePassed) {
  drivers::EmptyDriver empty_driver;
  uint8_t              array[4]{};

  drivers::Result result = empty_driver.Write(array, 0);
  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::INVALID_ARGUMENT);
}

TEST(Drivers, WriteShouldCallWriteImplOnce) {
  drivers::DummyDriver dummy_driver;
  EXPECT_CALL(dummy_driver, WriteImpl).Times(1);

  uint8_t array[6]{};
  dummy_driver.Write(array, sizeof(array));
}

TEST(Drivers, WritePassArgumentsToWriteImpl) {
  drivers::DummyDriver dummy_driver;
  static const int     BUFFER_SIZE = 6;
  const uint8_t        array[BUFFER_SIZE]{};

  EXPECT_CALL(dummy_driver, WriteImpl(array, BUFFER_SIZE)).Times(1);
  dummy_driver.Write(array, BUFFER_SIZE);
}

TEST(Drivers, WriteReturnWriteImplReturnValue) {
  drivers::DummyDriver  dummy_driver;
  static const uint32_t BUFFER_SIZE = 6;
  const uint8_t         array[BUFFER_SIZE]{};

  ON_CALL(dummy_driver, WriteImpl).WillByDefault(::testing::Return(BUFFER_SIZE));

  drivers::Result result = dummy_driver.Write(array, BUFFER_SIZE);
  EXPECT_EQ(std::get<uint32_t>(result), BUFFER_SIZE);
}

TEST(Drivers, WriteReturnWriteImplReturnValue2) {
  drivers::DummyDriver dummy_driver;
  ON_CALL(dummy_driver, WriteImpl).WillByDefault(::testing::Return(drivers::Status::FAIL));

  static const uint32_t BUFFER_SIZE = 8;
  const uint8_t         array[BUFFER_SIZE]{};

  drivers::Result result = dummy_driver.Write(array, BUFFER_SIZE);
  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::FAIL);
}

TEST(Drivers, WriteReturnNotImplementedIfWriteImpIsNotImplemented) {
  drivers::EmptyDriver  empty_driver;
  static const uint32_t BUFFER_SIZE = 10;
  const uint8_t         array[BUFFER_SIZE]{};

  const drivers::Result result = empty_driver.Write(array, BUFFER_SIZE);
  EXPECT_EQ(std::get<drivers::Status>(result), drivers::Status::NOT_IMPLEMENTED);
}