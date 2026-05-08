find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(accounts_core
    Account.cpp
    Account.h
    Credential.h
    CredentialType.h
)

target_link_libraries(accounts_core
    PUBLIC
        Qt6::Core
)

target_include_directories(accounts_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
