add_subdirectory(${CMAKE_SOURCE_DIR}/src/drivers ${CMAKE_CURRENT_BINARY_DIR}/src)

add_executable(
  unit_test_drivers
  unit_test_drivers.cpp
)
target_link_libraries(
  unit_test_drivers
  ${PROJECT_NAME}
  GTest::gtest_main
)

gtest_discover_tests(unit_test_drivers)