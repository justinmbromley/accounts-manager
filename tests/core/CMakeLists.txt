find_package(Qt6 REQUIRED COMPONENTS Test)

# Account
qt_add_executable(test_account
    account_test.cpp
)

target_link_libraries(test_account
    PRIVATE
        Qt6::Test
        accounts_core
)

add_test(NAME test_account COMMAND test_account)


# Account Summary
qt_add_executable(test_account_summary
    account_summary_test.cpp
)

target_link_libraries(test_account_summary
    PRIVATE
        Qt6::Test
        accounts_core
)

add_test(NAME test_account_summary COMMAND test_account_summary)


# Account Service
qt_add_executable(test_account_service
    account_service_test.cpp
)

target_link_libraries(test_account_service
    PRIVATE
        Qt6::Test
        accounts_core
        accounts_data
)

add_test(NAME test_account_service COMMAND test_account_service)


# Credential type
qt_add_executable(test_credential_type
    credential_type_test.cpp
)

target_link_libraries(test_credential_type
    PRIVATE
        Qt6::Test
        accounts_core
)

add_test(NAME test_credential_type COMMAND test_credential_type)


