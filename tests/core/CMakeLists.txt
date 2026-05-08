cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Test)

qt_add_executable(test_account
    account_test.cpp
)

target_link_libraries(test_account
    PRIVATE Qt6::Test
    PRIVATE accounts_core
)

add_test(NAME test_account COMMAND test_account)
