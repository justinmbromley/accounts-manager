find_package(Qt6 REQUIRED COMPONENTS Test)

qt_add_executable(test_in_memory_account_repository
    in_memory_account_repository_test.cpp
)

target_link_libraries(test_in_memory_account_repository
    PRIVATE
        Qt6::Test
        accounts_data
)

add_test(NAME test_in_memory_account_repository COMMAND test_in_memory_account_repository)
