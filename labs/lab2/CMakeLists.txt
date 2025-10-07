set(SOURCE "src") 
set(TESTS tests)
set(HEADER "headers")

message(STATUS "SOURCE path: ${SOURCE}")
message(STATUS "HEADER path: ${HEADER}")
message(STATUS "TESTS path: ${TESTS}")

include_directories(${HEADER})
add_library(lab2_array ${SOURCE}/array.cpp)
add_library(lab2_seven ${SOURCE}/seven.cpp)
target_link_libraries(lab2_seven PRIVATE lab2_array)

add_executable(lab2 main.cpp)
target_link_libraries(lab2 PRIVATE lab2_seven)

add_executable(lab2ArrayTest ${TESTS}/array_test.cpp)
target_link_libraries(lab2ArrayTest PRIVATE lab2_seven gtest_main)

add_executable(lab2SevenTest ${TESTS}/seven_test.cpp)
target_link_libraries(lab2SevenTest PRIVATE lab2_seven gtest_main)

enable_testing()

include(GoogleTest)
gtest_discover_tests(lab2ArrayTest)
gtest_discover_tests(lab2SevenTest)

#add_executable(Lab1Tests tests/tests.cpp)
#target_link_libraries(Lab1Tests PRIVATE gtest_main)
#target_include_directories(Lab1Tests PRIVATE src)
#add_test(NAME Lab1Tests COMMAND Lab1Tests)
