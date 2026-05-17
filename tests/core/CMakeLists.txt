find_package(Qt6 REQUIRED COMPONENTS Test)

qt_add_executable(test_account
    account_test.cpp
)

target_link_libraries(test_account
    PRIVATE
        Qt6::Test
        accounts_core
)

add_test(NAME test_account COMMAND test_account)


qt_add_executable(test_account_summary
    account_summary_test.cpp
)

target_link_libraries(test_account_summary
    PRIVATE
        Qt6::Test
        accounts_core
)

add_test(NAME test_account_summary COMMAND test_account_summary)
