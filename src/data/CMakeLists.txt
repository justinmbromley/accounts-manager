find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(accounts_data
    InMemoryAccountRepository.cpp
    InMemoryAccountRepository.h
)

target_link_libraries(accounts_data
    PUBLIC
        Qt6::Core
        accounts_core
)

target_include_directories(accounts_data
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
